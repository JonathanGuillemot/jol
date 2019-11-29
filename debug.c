#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"
#include "tools.h"
#include "jstr.h"

/* MAIN */
int main (int argc, char ** argv) {
	
	jstr j1 = regstr_to_jstr ("abc");
	jstr j2 = regstr_to_jstr ("abcd");
	printf("%d\n", jstr_compare (j1, j2));
	jstr_destroy (j1);
	jstr_destroy (j2);

	return EXIT_SUCCESS;
}
//-1 si j1 < j2 // 0 si j1 egale a j2 // 1 si j1 > J2 (ordre lexicographique)
