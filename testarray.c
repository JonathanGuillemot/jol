#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"
#include "tools.h"

/* MAIN */
int main (int argc, char ** argv) {
	
	intarray array = empty_intarray_create (2);
	ext_intarray_set(array, 0, 1);
	ext_intarray_set(array, 1, 5);
	ext_intarray_debug(array);

	for (int i = 0; i < 30; i++) {
		intarray_add (array, 2*i + i);
		ext_intarray_debug (array);
	}

	intarray_destroy (array);
	
	return EXIT_SUCCESS;
}
