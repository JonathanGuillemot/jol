#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"


/* MAIN */
int main (int argc, char ** argv) {
	
	intarray array = intarray_create (12);
	int i;
	for (i=0; i < array.len; i++)
		intarray_set(array, i, -2*i+8);
	intarray_debug (array);
	
	intarray_sort1 (array);

	intarray_debug(array);

	intarray_destroy (array);	
	return EXIT_SUCCESS;
}
