#ifndef __CHARRAY2D_H__
#define __CHARRAY2D_H__

#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "file.h"

typedef struct _charray S_charray;
typedef struct _charray* charray;

/* Methode 1 : char **; adressage lent | utilisation simple
 * Methode 2 : char *; adressage rapide | utilisation plus compliquee
 * Methode 3 : char * / char ** ; adressage rapide | utilisation simple */
struct _charray {
	int w;		/*width*/
	int h;		/*height*/
	char bg; 	/*charactere de fond*/
	char* data;
	char ** pixel;	
};

charray charray_create (int w, int h, char bg);

void charray_destroy (charray* A);

void charray_debug (charray A);

void charray_fill (charray A, char bg);

char charray_get (charray A, int x, int y);

void charray_set (charray A, int x, int y, char value);

// src et tar doivent etre differents
void charray_copy (charray src, int sx1, int sy1,
		   charray tar, int tx1, int ty1,
		   int w, int h);

void charray_copy_alpha (charray src, int sx1, int sy1,
		   charray tar, int tx1, int ty1,
		   int w, int h);

charray charray_crop (charray A, int x1, int y1, int w, int h);

charray charray_clone (charray A);

/* primitives geometriques */
void charray_draw_hor_line (charray A, int x1, int x2, int y, char c);
void charray_draw_ver_line (charray A, int x, int y1, int y2, char c);

void charray_draw_empty_box (charray A, int x1, int y1, int x2, int y2, char c);
void charray_draw_filled_box (charray A, int x1, int y1, int x2, int y2, char c);

void charray_draw_disk (charray A, int cx, int cy, float radius, char c);

void charray_write (charray A, file F);
void charray_save (charray A, char* filename); 

charray charray_read (file F);
charray charray_load (char* filename);
#endif
