#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"
#include "tools.h"
#include "jstr.h"
#include "stringarray.h"

/* MAIN */
int main (int argc, char ** argv) {
	tools_memory_init ();
	
	float a=2;
	int i, n=24;

	printf("puiss_iter(%f, %d) = %f\n", a, n, puiss_iter (a, n));
	printf("puiss_rec(%f, %d) = %f\n", a, n, puiss_rec (a, n));
	printf("puiss_alex(%f, %d) = %f\n", a, n, puiss_alex (a, n));

	for (i=0; i < 100000000; i++)
		puiss_alex(a, n);


	tools_memory_check_at_end_of_app ();
						 
	return EXIT_SUCCESS;
}
