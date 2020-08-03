#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "intarray.h"
#include "tools.h"
#include "jstr.h"
#include "stringarray.h"
#include "charray2D.h"
#include "file.h"
#include "KVdata.h"
#include "image.h"

int main (int argc, char ** argv) {
	tools_memory_init ();
	image img = image_load ("TOTO.ppm");
	if (img == NULL)
		fprintf (stderr, "Unable to read .ppm file.\n");
	else {
		image_save (img, "TITI.ppm");
		image_destroy (&img);
	}
	tools_memory_check_at_end_of_app ();

	return EXIT_SUCCESS;
}
