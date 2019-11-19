#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "intarray.h"

int main (int argc, char ** argv) {
	intarray array = intarray_create (argc - 1);
	int real_len_of_array = 0;
	int i;
	
	for (i=1; i < argc; i++) {
		int ok, n = safe_string_to_int(argv[i], &ok);
		if (ok) {
			intarray_set (array, real_len_of_array, n);
			real_len_of_array ++;
		}
	}
	array.len = real_len_of_array; // BIDOUILLAGE DEGUEU

	intarray_debug(array);
	printf("Somme = %d\n", intarray_sum(array));
	printf("Moyenne = %f\n", intarray_average(array));
	printf("Mediane = %f\n", intarray_median(array));

	intarray_destroy (array);
	return EXIT_SUCCESS;
}


