#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "intarray.h"
#include "tools.h"
#include "jstr.h"
#include "stringarray.h"

/* MAIN */
int main (int argc, char ** argv) {
	tools_memory_init ();
	intarray divs = standard_empty_intarray_create();
	int n = 1000;
	int i;
	int cpt = 0;
	if (argc > 1) {
		int ok;
		int v = safe_string_to_int (argv[1], &ok);
		if (ok == 1)
			n = v;
	}

	if (n < 0) {
		printf("%d est negatif, nous cherchons les diviseurs de  -%d\n", n, -n);
		n =-n;
	}

	for (i = 1; i <= sqrt (n) + 1; i++) {
		if (n % i == 0)	{
			intarray_add (divs, i);
			intarray_add(divs, n/i);
		}
	}
	
	intarray_sort1 (divs);	
	intarray_debug (divs);
	printf("\n\n");
	printf("Il y a %d diviseurs de %d\n\n", divs->len, n);
	
	intarray_destroy (divs);
	tools_memory_check_at_end_of_app ();
						 
	return EXIT_SUCCESS;
}
