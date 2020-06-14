#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "tools.h"
#include "file.h"

file file_open (char * filename, int mode) {
	file F = (file) tools_malloc (sizeof (struct _file));
	if (mode == FILE_READ_ONLY) {
		F->cursor = FILE_BUFFER_SIZE;
		F->len = FILE_BUFFER_SIZE;
		F->handler = open (filename, O_RDONLY, 00600);
	}
	else { // assume mode == FILE_WRITE_ONLY
		F->cursor = 0;
		F->len = 0;
		F->handler = open (filename, O_WRONLY | O_CREAT | O_TRUNC, 00600);
	}

	if (F->handler == -1) {
		tools_free (F, sizeof (struct _file));
		fprintf (stderr, "file_open : unable to open file %s\n", filename);
		return NULL;
	}
	F->filename = regstr_clone (filename);
	F->mode = mode;
	F->buffer = (char*) tools_malloc (sizeof (char) * FILE_BUFFER_SIZE);

	return F;
}

void file_close (file * FF) {

	file F = *FF;

	if (F == NULL) {
		fprintf (stderr, "file_close : *FF is a NULL pointer.\n");
		return;
	}

	if ((F->mode == FILE_WRITE_ONLY) && (F->cursor != 0) && (F->cursor != FILE_BUFFER_SIZE)) {
		write (F->handler, F->buffer, F->cursor);
	}
	close (F->handler);
//	tools_free (F->filename, sizeof (char) * (strlen (F->filename) + 1));
	regstr_destroy (&(F->filename));
	tools_free (F->buffer, sizeof (char) * FILE_BUFFER_SIZE);
	tools_free (F, sizeof (struct _file));

	*FF = NULL;
}

// private
int file_read_char_aux (file F, bool go_to_next) {

	if (F->mode == FILE_WRITE_ONLY) {
		fprintf (stderr, "file_read_char : file %s is not opened in read mode.\n", F->filename);
		return FILE_EOF;
	}

	if (F->cursor < F->len) {
		char c = F->buffer[F->cursor];
		if (go_to_next)
			F->cursor ++;
		return (int) c;
	}		
	if (F->cursor > F->len) {
		fprintf (stderr, "file_read_char : erreur d'implementation\n");	
		return FILE_EOF;
	}
	if (F->cursor == F->len) {
		F->len = read (F->handler, F->buffer ,FILE_BUFFER_SIZE);
		if (F->len == 0)
			return FILE_EOF;
		else {
			if (go_to_next)
				F->cursor = 1;
			else
				F->cursor = 0;
			return (int) F->buffer[0];
		}
	}
}

int file_read_char_and_stop (file F) {
	return file_read_char_aux (F, FALSE);
}
void file_go_to_next_char (file F) {
	 F->cursor++;
}

int file_read_char (file F) {
	return file_read_char_aux (F, TRUE);
}

void file_write_char (file F, char c) {

	if (F->mode == FILE_READ_ONLY) {
		fprintf (stderr, "file_write_char : file %s is not opened in write mode.\n", F->filename);
		return ;
	}

	if (F->cursor > FILE_BUFFER_SIZE) {
		fprintf (stderr, "file_write_char : erreur d'implementation.\n");
		return;
	}
	if (F->cursor < FILE_BUFFER_SIZE) {
		F->buffer[F->cursor] = c;
		F->cursor++;
	}
	if (F->cursor == FILE_BUFFER_SIZE) {
		write (F->handler, F->buffer, FILE_BUFFER_SIZE);
		F->cursor = 0;
	}
}

void file_write_string (file F, char* str) {
	int i; 
	for (i=0; str[i] != '\0'; i++)
		file_write_char (F, str[i]);
}

void file_write_text_int (file F, int n) {
	char * str = int_to_regstr (n);
	file_write_string (F, str);
	regstr_destroy (&str);
}

void file_write_binary_int32 (file F, int n) {
	file_write_char (F, n>>24);
	file_write_char (F, (n>>16) & 0xFF);
	file_write_char (F, (n>>8) & 0xFF);
	file_write_char (F, (n) & 0xFF);
}

/*void file_write_binary_int64 (file F, int n) {
	file_write_char (F, n>>48);
	file_write_char (F, (n>>32) & 0xFF);
	file_write_char (F, (n>>16) & 0xFF);
	file_write_char (F, (n) & 0xFF);
}*/

void file_read_binary_int32 (file F, int*nn, bool* eof) {
	int i , n = 0;
	for (i = 0; i < 4; i++) {
		int a = file_read_char (F);
		if (a == FILE_EOF) {
			*eof = TRUE;
			*nn = -1;
			return;
		}
		n = (n << 8) | a;
	}
	
	*eof = FALSE;
	*nn = n;
}

void file_read_next_text_int (file F, int* nn, bool* is_integral, bool* eof) {
	int c = file_read_char_and_stop (F);
	while ((c != FILE_EOF) && (c == ' ') || (c == '\n') || (c == 13) || (c == 10)) {
		file_go_to_next_char (F);
		c = file_read_char_and_stop (F);
	}
	if (c == FILE_EOF) {
		*is_integral = FALSE;
		*eof = TRUE;
		*nn = -1;
		return;
	}

	file_read_text_int (F, nn, is_integral, eof);
}
void file_read_text_int (file F, int* nn, bool* is_integral, bool* eof) {
	int n = 0;
	int c = file_read_char (F);

	if (c == FILE_EOF) {
		*is_integral = FALSE;
		*eof = TRUE;
		*nn = -1;
		return;
	} else if ((c < '0') || (c > '9')) {
		*nn = -1;
		*is_integral = FALSE;
		*eof = FALSE;
		return;
	}

	while ((c != FILE_EOF) && (c >= '0') && (c <= '9')) {
		n *= 10;
		n += ((char) c) - '0';
		c = file_read_char (F);
	}

	*is_integral = TRUE;
	*eof = FALSE;
	*nn = n;
}

int file_read (file F, void* bbuffer, int nb_to_read) {
	char * buffer = (char*) bbuffer;
	int i = 0, c;
	c = file_read_char (F);
	while ((i < nb_to_read) && (c != FILE_EOF)) {
		buffer[i] = c;
		i++;
		c = file_read_char (F);
	}
	return i;
}

void file_write (file F, void* bbuffer, int nb_to_write) {
	char * buffer = (char*) bbuffer;
	int i;
	for (i = 0; i < nb_to_write; i++)
		file_write_char (F, buffer[i]);
}

void file_write_str (file F, char* str) {
	int i;
	for (i = 0; str[i] != '\0'; i++)
		file_write_char (F, str[i]);
}

void file_read_str_of_len (file F, int len, char ** sstr, bool* eof) {
	char* str = (char*) tools_malloc (sizeof (char) * (len + 1));
	int i;
	for (i = 0; i < len; i++) {
		int c = file_read_char (F);
		if (c == FILE_EOF) {
			str[len] = '\0';
			*eof = TRUE;
			*sstr = str;
			return;
		}
		str[i] = (char) c;
	}
	str[len] = '\0';
	*eof = FALSE;
	*sstr = str;
}
