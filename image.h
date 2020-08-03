#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "file.h"

typedef unsigned char imgcmp;
typedef unsigned int imgcol;

imgcol image_make_color (imgcmp r, imgcmp g, imgcmp b);
void image_get_color_cmp (imgcol c, imgcmp * r, imgcmp * g, imgcmp * b); 
void image_color_debug (imgcol c);

typedef struct _image S_image;
typedef struct _image* image;

/* Methode 1 : char **; adressage lent | utilisation simple
 * Methode 2 : char *; adressage rapide | utilisation plus compliquee
 * Methode 3 : char * / char ** ; adressage rapide | utilisation simple */
struct _image {
	int w;		/*width*/
	int h;		/*height*/
	imgcol bg; 	/*charactere de fond*/
	imgcol* data;
	imgcol ** pixel;	
};

image image_create (int w, int h, imgcol bg);

void image_destroy (image* A);

void image_debug (image A);

void image_fill (image A, imgcol bg);

imgcol image_get (image A, int x, int y);

void image_set (image A, int x, int y, imgcol value);

// src et tar doivent etre differents
void image_copy (image src, int sx1, int sy1,
		   image tar, int tx1, int ty1,
		   int w, int h);

void image_copy_alpha (image src, int sx1, int sy1,
		   image tar, int tx1, int ty1,
		   int w, int h);

image image_crop (image A, int x1, int y1, int w, int h);

image image_clone (image A);

/* primitives geometriques */
void image_draw_hor_line (image A, int x1, int x2, int y, imgcol c);
void image_draw_ver_line (image A, int x, int y1, int y2, imgcol c);

void image_draw_empty_box (image A, int x1, int y1, int x2, int y2, imgcol c);
void image_draw_filled_box (image A, int x1, int y1, int x2, int y2, imgcol c);

void image_draw_disk (image A, int cx, int cy, float radius, imgcol c);

void image_write (image A, file F);
void image_save (image A, char* filename); 
image image_read (file F);
image image_load (char * filename);
#endif
