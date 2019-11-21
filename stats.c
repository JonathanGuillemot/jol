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

	if (array.len == 0) {
		printf("Aucun nombre. Statistiques impossibles.\n");
		intarray_destroy(array);
		return EXIT_SUCCESS;
	}

	printf("\nVous avez entre les entiers suivants :\n");
	intarray_debug(array);
	{
		int min = intarray_get_min (array);
		int max = intarray_get_max (array);
		printf("\nQuelques statistiques :\n");
		printf("Mimimum = %d\n", min);
		printf("Maximum = %d\n", max);
		printf("Etendue = %d\n", max-min);
		printf("Somme = %d\n", intarray_sum(array));
		printf("Moyenne = %f\n", intarray_average(array));
		printf("Mediane = %f\n", intarray_median(array));
	}
	intarray_destroy (array);
	return EXIT_SUCCESS;
}


