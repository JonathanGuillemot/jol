#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"
#include "tools.h"
#include "jstr.h"

/* MAIN */
int main (int argc, char ** argv) {

	jstr S1 = standard_empty_jstr_create ();
	int i;
	for (i = 1; i < argc; i ++) {
		jstr tmp = regstr_to_jstr (argv[i]);
		D_jstr_concact (S1, tmp);
		jstr_destroy (tmp);
	}
	ext_jstr_debug (S1);
	jstr_destroy (S1);
	return EXIT_SUCCESS;
}
