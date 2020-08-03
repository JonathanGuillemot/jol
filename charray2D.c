#include <stdlib.h>
#include <stdio.h>

#include "tools.h"
#include "charray2D.h"
#include "file.h"

/*
	format de fichier :

	chaine d'identification : ".charray01"

	int32 => largeur w du charray.
	int32 => hauteur h du charray.

	w * h octets represantant les chars contenus dans l'ordre de haut en bas et de gauche a droite.
*/

/* fonctions privees (au module charray) : ne sont pas dans charray.h */
void charray_alloc (charray A, int w, int h) {
	A->data = tools_malloc(sizeof (char) * w * h);
	A->pixel = tools_malloc (sizeof  (char*) * h);	
	int i;
	for (i=0; i < h; i++) A->pixel[i] = A->data + i * A->w * sizeof(char);
}

charray charray_create (int w, int h, char bg) {
	charray A = tools_malloc (sizeof (struct _charray));
	A->w = w; A->h = h; A->bg = bg;
	charray_alloc (A, w, h);
	charray_fill (A, bg);
	return A;
}

void charray_fill (charray A, char bg) {
	char * ptr = A->data;
	/*int i, j;
	for (i = 0; i < A->h; i++) {
		for (j = 0; j < A->w; j++) {
			*ptr = bg;
			ptr++;
		}	
	}*/
	int i;
	for (i=0; i < A->h * A->w; i++) {
		ptr[i] = bg;
	}
}

void charray_destroy (charray* AA) {
	charray A = *AA;
	int i;
	tools_free (A->pixel, sizeof(char*) * A->h);
	tools_free (A->data, sizeof(char) * A->h * A->w);
	tools_free (A, sizeof(struct _charray));
	*AA = NULL;
}

void charray_debug (charray A) {
	fprintf(stderr, "\n\n");
	char * ptr = A->data;
	int i, j;
	for (i = 0; i < A->h; i++) {
		for (j = 0; j < A->w; j++) {
			fprintf (stderr, "%c ", *ptr);
			ptr ++;
		}
		fprintf(stderr, "\n");
	}
	fprintf(stderr, "\n\n");
}

char charray_get (charray A, int x, int y) {
	if ((x < 0) || (x >= A->w) || (y < 0) || (y >= A->h)) {
		fprintf(stderr, "\ncharray_get : (%d; %d) is out of bounds.", x, y);
		return A->bg;
	}
	//return A->data[A->w * y + x];
	return A->pixel[y][x];
}

void charray_set (charray A, int x, int y, char value) {
	if ((x < 0) || (x >= A->w) || (y < 0) || (y >= A->h)) {
		fprintf(stderr, "charray_get : (%d; %d) is out of bounds.\n", x, y);
		return;
	}
	//A->data[A->w * y + x] = value;
	A->pixel[y][x] = value;
}


void charray_copy_aux (charray src, int sx1, int sy1,
		   charray tar, int tx1, int ty1,
		   int w, int h,
		   int alpha) {
	if (src == tar) {
		fprintf(stderr, "charray_copy : src and tar are the same charray\n");
		return;
	}
	
	int ex1 = sx1 + w - 1;
	int ey1 = sy1 + h - 1;
	int_normalize_and_warn (&sx1, 0, src->w -1);
	int_normalize_and_warn (&sy1, 0, src->h -1);
	int_normalize_and_warn (&ex1, 0, src->w -1);
	int_normalize_and_warn (&ey1, 0, src->h -1);
	w = ex1 - sx1 + 1;
	h = ey1 - sy1 + 1;

	int x, y, xx, yy;
	int error = 0;
	for (y=0; y < h; y++) {
		xx = tx1;
		yy = ty1 + y;
		for (x = 0; x < w; x++) {
			if ((xx >= 0) && (yy >= 0) && (xx < tar->w) && (yy < tar->h)) {
				char c = src->pixel[sy1 + y][sx1 + x];
				if ((alpha == 1) && (c == src->bg))
					tar->pixel[yy][xx] = tar->bg;
				else
					tar->pixel[yy][xx] = c;
			}
			else
				error = 1;
			xx++;
		}
	}
	if (error == 1) fprintf (stderr, "charray_copy : out of bounds in target.\n");
}

void charray_copy (charray src, int sx1, int sy1,
		   charray tar, int tx1, int ty1,
		   int w, int h) {
	charray_copy_aux (src, sx1, sy1, tar, tx1, ty1, w, h, 0);
}

void charray_copy_alpha (charray src, int sx1, int sy1,
		   charray tar, int tx1, int ty1,
		   int w, int h) {
	charray_copy_aux (src, sx1, sy1, tar, tx1, ty1, w, h, 1);
}

charray charray_crop (charray A, int x1, int y1, int w, int h) {
	charray B = charray_create (w, h, A->bg);
	charray_copy (A, x1, y1, B, 0, 0, w, h);
	return B;
}

charray charray_clone (charray A) {
	return charray_crop (A, 0, 0, A->w, A->h);
}

void charray_draw_hor_line (charray A, int x1, int x2, int y, char c) {
	char * ptr = A->data + x1 + A->w * y;
	int x;
	for (x=x1; x<=x2; x++) {
		*ptr = c;
		ptr++;
	}	
}
void charray_draw_ver_line (charray A, int x, int y1, int y2, char c) {
	char * ptr = A->data + x + A->w * y1;
	int y;
	for (y=y1; y<=y2; y++){
		*ptr = c;
		ptr += A->w;
	}
}

void charray_draw_empty_box (charray A, int x1, int y1, int x2, int y2, char c) {
	charray_draw_ver_line (A, x1, y1, y2, c);
	charray_draw_ver_line (A, x2, y1, y2, c);
	charray_draw_hor_line (A, x1 + 1, x2 - 1, y1, c); 
	charray_draw_hor_line (A, x1 + 1, x2 - 1, y2, c); 
}
void charray_draw_filled_box (charray A, int x1, int y1, int x2, int y2, char c) {
	int x, y;
	for (y=y1; y<=y2; y++) {
		char* ptr = A->data + x1 + A->w * y;
		for (x=x1; x<=x2; x++) {
			*ptr = c;
			ptr++;
		}
	}
}

void charray_draw_disk (charray A, int cx, int cy, float radius, char c) {
	int x1 = cx - radius - 2;
	int x2 = cx + radius + 2;
	int y1 = cy - radius - 2;
	int y2 = cy + radius + 2;

	int_normalize (&x1, 0, A->w -1);
	int_normalize (&x2, 0, A->w -1);
	int_normalize (&y1, 0, A->w -1);
	int_normalize (&y2, 0, A->w -1);

	int x, y;
	for (y = y1; y <= y2; y++) {
		char* ptr = A->data + x1 + y * A->w;
		for (x = x1; x <= x2; x++) {
			if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius)
				*ptr = c;
			ptr++;		
		}	
	}
}

void charray_write (charray A, file F) {
	int i;
	file_write_str (F, ".charray01");
	file_write_binary_int32 (F, A->w);
	file_write_binary_int32 (F, A->h);
	file_write_char (F, A->bg);
	for (i = 0; i < A->w * A->h; i++)
		file_write_char (F, A->data[i]);	
}

void charray_save (charray A, char* filename) {
	file F = file_open (filename, FILE_WRITE_ONLY);
	charray_write (A, F);
	file_close (&F);
}

// retourne NULL si le charray n'a pas pu etre lu
charray charray_read (file F) {
	char* format_str = NULL; bool eof = FALSE;
	file_read_str_of_len (F, 10, &format_str, &eof);	
	if (eof) {
		fprintf (stderr, "charray_read : premature end of file.\n");
		regstr_destroy_of_len (&format_str, 10);
		return NULL;
	}
	if (!regstr_equal (".charray01", format_str)) {
		fprintf (stderr, "charray_read : uncorrect file format\n");
		regstr_destroy_of_len (&format_str, 10);
		return NULL;
	}
	regstr_destroy_of_len (&format_str, 10);
	int w; int h; charray A = NULL;
	int i;
	file_read_binary_int32 (F, &w, &eof);
	if (eof) {
		fprintf (stderr, "charray_read : premature end of file.\n");
		return NULL;
	}
	file_read_binary_int32 (F, &h, &eof);
	if (eof) {
		fprintf (stderr, "charray_read : premature end of file.\n");
		return NULL;
	}

	A = (charray) tools_malloc (sizeof (struct _charray));

	int c = file_read_char (F);
	if (c == FILE_EOF) {
		charray_destroy (&A);
		fprintf (stderr, "charray_read : premature end of file.\n");
		return NULL;
	} else
		A->bg = (char) c;


	A->w = w; A->h = h;
	charray_alloc (A, w, h);
	for (i=0; i < w * h; i++) {
		int c = file_read_char (F);
		if (c == FILE_EOF) {
			charray_destroy (&A);
			fprintf (stderr, "charray_read : premature end of file.\n");
			return NULL;
		}
		A->data[i] = (char) c;
	}
	return A;
}

charray charray_load (char* filename) {
	file F = file_open (filename, FILE_READ_ONLY);
	charray A = charray_read (F);
	file_close (&F);
	return A;
}
