#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"
#include "tools.h"
#include "jstr.h"
#include "stringarray.h"

/* MAIN */
int main (int argc, char ** argv) {
	tools_memory_init ();
	
	stringarray s1 = standard_empty_stringarray_create ();
	
	for (int i = 0; i < 20; i++)
		stringarray_add (s1, regstr_to_jstr ("XXX"));
	
	ext_stringarray_debug(s1);
	
	hard_stringarray_destroy(s1);
	
	tools_memory_check_at_end_of_app ();

	return EXIT_SUCCESS;
}
