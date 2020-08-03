#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "jstr.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILE_BUFFER_SIZE 4096

#define FILE_READ_ONLY 0
#define FILE_WRITE_ONLY 1

#define FILE_EOF 500

typedef struct _file* file;

struct _file {
	char * filename;
	int handler;
	int mode;
	char* buffer;
	int len; 	// 0 <= len <= FILE_BUFFER_SIZE
	int cursor; 	// 0 <= cursor <= len - 1
};

file file_open (char * filename, int mode);
void file_close (file * FF);
int file_read_char (file F);	// return EOF when the end of file F is reached
int file_read_char_and_stop (file F);
void file_go_to_next_char (file F);
void file_write_char (file F, char c);
void file_write_string (file F, char* str); 
void file_write_text_int (file F, int n);
void file_write_binary_int32 (file F, int n); 

//void file_write_binary_int64 (file F, int n); 
void file_read_binary_int32 (file F, int* n, bool* eof);

// Tente de lire un int a la position actuelle dans F
void file_read_text_int (file F, int* n, bool* is_integral, bool* eof);

// Tente de lire le prochain int qui apparait dans F
// Apres avoir ignore tous les caracteres : ' ', '\n', CR, LF...
void file_read_next_text_int (file F, int* n, bool* is_integral, bool* eof);
void file_read_next_text_str (file F, char** str, bool *eof);

// homologue de read (bufferise) ; retourne le nombre d'octet effectivement lus
int file_read (file F, void* buffer, int nb_to_read);

// homologue de write
void file_write (file F, void* buffer, int nb_to_write);

void file_write_str (file F, char* str);
void file_read_str_of_len (file F, int len, char ** sstr, bool* eof);
void file_read_str_until_sep (file F, char** str, bool *eof); 
void file_go_to_next_line (file F);
#endif
