#include <stdlib.h>
#include <stdio.h>

#include "tools.h"
#include "image.h"
#include "file.h"

/*
	format de fichier :

	chaine d'identification : ".image01"

	int32 => largeur w du image.
	int32 => hauteur h du image.

	w * h octets represantant les chars contenus dans l'ordre de haut en bas et de gauche a droite.
*/

imgcol image_make_color (imgcmp r, imgcmp g, imgcmp b) {
	return ((r << 16) | (g << 8) | b);
}

void image_get_color_cmp (imgcol c, imgcmp * r, imgcmp * g, imgcmp * b) {
	*r = c >> 16;
	*g = (c >> 8) & 0xFF;
	*b = c & 0xFF;
}

void image_color_debug (imgcol c) {
	imgcmp r, g, b;
	image_get_color_cmp (c, &r, &g, &b);
	fprintf (stderr, "C (%d ; %d ; %d)\n", r, g, b);
}

/* fonctions privees (au module image) : ne sont pas dans image.h */
void image_alloc (image A, int w, int h) {
	A->data = tools_malloc(sizeof (imgcol) * w * h);
	A->pixel = tools_malloc (sizeof  (imgcol*) * h);	
	int i;
	for (i=0; i < h; i++) A->pixel[i] = A->data + i * A->w * sizeof(imgcol);
}

image image_create (int w, int h, imgcol bg) {
	image A = tools_malloc (sizeof (struct _image));
	A->w = w; A->h = h; A->bg = bg;
	image_alloc (A, w, h);
	image_fill (A, bg);
	return A;
}

void image_fill (image A, imgcol bg) {
	imgcol * ptr = A->data;
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

void image_destroy (image* AA) {
	image A = *AA;
	int i;
	tools_free (A->pixel, sizeof(imgcol*) * A->h);
	tools_free (A->data, sizeof(imgcol) * A->h * A->w);
	tools_free (A, sizeof(struct _image));
	*AA = NULL;
}

void image_debug (image A) {
	fprintf(stderr, "\n\n");
	imgcol * ptr = A->data;
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

imgcol image_get (image A, int x, int y) {
	if ((x < 0) || (x >= A->w) || (y < 0) || (y >= A->h)) {
		fprintf(stderr, "\nimage_get : (%d; %d) is out of bounds.", x, y);
		return A->bg;
	}
	//return A->data[A->w * y + x];
	return A->pixel[y][x];
}

void image_set (image A, int x, int y, imgcol value) {
	if ((x < 0) || (x >= A->w) || (y < 0) || (y >= A->h)) {
		fprintf(stderr, "image_get : (%d; %d) is out of bounds.\n", x, y);
		return;
	}
	//A->data[A->w * y + x] = value;
	A->pixel[y][x] = value;
}


void image_copy_aux (image src, int sx1, int sy1,
		   image tar, int tx1, int ty1,
		   int w, int h,
		   int alpha) {
	if (src == tar) {
		fprintf(stderr, "image_copy : src and tar are the same image\n");
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
				imgcol c = src->pixel[sy1 + y][sx1 + x];
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
	if (error == 1) fprintf (stderr, "image_copy : out of bounds in target.\n");
}

void image_copy (image src, int sx1, int sy1,
		   image tar, int tx1, int ty1,
		   int w, int h) {
	image_copy_aux (src, sx1, sy1, tar, tx1, ty1, w, h, 0);
}

void image_copy_alpha (image src, int sx1, int sy1,
		   image tar, int tx1, int ty1,
		   int w, int h) {
	image_copy_aux (src, sx1, sy1, tar, tx1, ty1, w, h, 1);
}

image image_crop (image A, int x1, int y1, int w, int h) {
	image B = image_create (w, h, A->bg);
	image_copy (A, x1, y1, B, 0, 0, w, h);
	return B;
}

image image_clone (image A) {
	return image_crop (A, 0, 0, A->w, A->h);
}

void image_draw_hor_line (image A, int x1, int x2, int y, imgcol c) {
	imgcol * ptr = A->data + x1 + A->w * y;
	int x;
	for (x=x1; x<=x2; x++) {
		*ptr = c;
		ptr++;
	}	
}
void image_draw_ver_line (image A, int x, int y1, int y2, imgcol c) {
	imgcol * ptr = A->data + x + A->w * y1;
	int y;
	for (y=y1; y<=y2; y++){
		*ptr = c;
		ptr += A->w;
	}
}

void image_draw_empty_box (image A, int x1, int y1, int x2, int y2, imgcol c) {
	image_draw_ver_line (A, x1, y1, y2, c);
	image_draw_ver_line (A, x2, y1, y2, c);
	image_draw_hor_line (A, x1 + 1, x2 - 1, y1, c); 
	image_draw_hor_line (A, x1 + 1, x2 - 1, y2, c); 
}
void image_draw_filled_box (image A, int x1, int y1, int x2, int y2, imgcol c) {
	int x, y;
	for (y=y1; y<=y2; y++) {
		imgcol* ptr = A->data + x1 + A->w * y;
		for (x=x1; x<=x2; x++) {
			*ptr = c;
			ptr++;
		}
	}
}

void image_draw_disk (image A, int cx, int cy, float radius, imgcol c) {
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
		imgcol* ptr = A->data + x1 + y * A->w;
		for (x = x1; x <= x2; x++) {
			if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius)
				*ptr = c;
			ptr++;		
		}	
	}
}

void image_write (image A, file F) {
	int i;
	file_write_str (F, "P6\n");
	file_write_text_int (F, A->w);
	file_write_char (F, ' ');
	file_write_text_int (F, A->h);
	file_write_char (F, '\n');
	file_write_str (F, "255\n");
	for (i = 0; i < A->w * A->h; i++) {
		imgcmp r, g, b;
		image_get_color_cmp (A->data[i], &r, &g, &b);
		file_write_char (F, (char) r);
		file_write_char (F, (char) g);	
		file_write_char (F, (char) b);	
	}
}

void image_save (image A, char* filename) {
	file F = file_open (filename, FILE_WRITE_ONLY);
	image_write (A, F);
	file_close (&F);
}

void image_read_ppm_ignore_comments (file F) {
	while (1) {
		int c = file_read_char_and_stop (F);
		if (c != '#')
			return;
		while ((c != 13) && (c != 10) && (c != '\n') && (c != FILE_EOF)) {
			file_go_to_next_char (F);
			c = file_read_char_and_stop (F);
		}
		if (c != FILE_EOF)
			file_go_to_next_char (F);
	}
}

// retourne NULL si le image n'a pas pu etre lu
image image_read (file F) {
	char P = file_read_char (F);
	char six = file_read_char (F);
	int w, h, compomax;
	bool is_integral, eof;
	if ((P != 'P') || (six != '6')) {
		fprintf (stderr, "image_read : string 'P6' not found.\n");
		return NULL;
	}

	file_go_to_next_line (F);
	image_read_ppm_ignore_comments (F);

	file_read_next_text_int (F, &w, &is_integral, &eof);
	if (eof || (!is_integral)) {
		fprintf (stderr, "image_read : unable to read image width.\n");
		return NULL;
	}
	file_read_next_text_int (F, &h, &is_integral, &eof);
	if (eof || (!is_integral)) {
		fprintf (stderr, "image_read : unable to read image width.\n");
		return NULL;
	}

	file_go_to_next_line (F);
	image_read_ppm_ignore_comments (F);

	file_read_next_text_int (F, &compomax, &is_integral, &eof);
	if (eof || (!is_integral)) {
		fprintf (stderr, "image_read : unable to read image width.\n");
		return NULL;
	}

	if (compomax != 255) {
		fprintf (stderr, "image_read : compomax should be 255.\n");
		fprintf (stderr, "%d was found instead\n", compomax);
		return NULL;
	}
	char newline = file_read_char (F);
	if (newline != '\n') {
		fprintf (stderr, "image_read : no newline found.\n");
		fprintf (stderr, "%d was found instead\n", newline);
		return NULL;
	}
	image img = image_create (w, h, 0);
	int i;
	for (i = 0; i < w * h; i++) {
		int r, g, b;
		r = file_read_char (F);	
		g = file_read_char (F);	
		b = file_read_char (F);	
		if (r == FILE_EOF || g == FILE_EOF || b == FILE_EOF) {
			fprintf (stderr, "image_read : premature end of file.\n");
			image_destroy (&img);
			return NULL;
		}
		imgcmp rr = (imgcmp) r;
		imgcmp gg = (imgcmp) g;
		imgcmp bb = (imgcmp) b;
		img->data[i] = image_make_color (rr, gg, bb);
	}
	return img;
}

image image_load (char* filename) {
	file F = file_open (filename, FILE_READ_ONLY);
	image A = image_read (F);
	file_close (&F);
	return A;
}
