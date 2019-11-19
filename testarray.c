#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"
#include "tools.h"

/* MAIN */
int main (int argc, char ** argv) {
	char * n = "-345";
	printf("%d\n", string_to_int(n)); 	
	return EXIT_SUCCESS;
}
