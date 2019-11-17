#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"


/* MAIN */
int main (int argc, char ** argv) {
	intarray array = intarray_create (10);
	intarray_set (array, 0, 9);
	int i;
	for (i=1; i < array.len; i++)
		intarray_set(array, i, 2*i - array.data[i-1]);
	intarray_debug (array);
	
	printf("La somme du tableau est : %d\n", intarray_sum (array));

	printf("La moyenne du tableau est : %f\n", intarray_average (array));	
	
	printf("La mediane du tableau est : %f\n", intarray_median (array));	

	intarray_debug(array);

	intarray_destroy (array);	
	return EXIT_SUCCESS;
}
