#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"
#include "tools.h"
#include "jstr.h"
#include "stringarray.h"

/* MAIN */
int main (int argc, char ** argv) {
	
	tools_memory_init ();

	jstr j1 = regstr_to_jstr ("salut");
	jstr j2 = regstr_to_jstr ("hello");
	stringarray s1 = standard_empty_stringarray_create ();
	stringarray_add (s1, j1);
	stringarray_add (s1, j2);
	hard_stringarray_destroy (s1);

	tools_memory_check_at_end_of_app ();

	return EXIT_SUCCESS;
}
