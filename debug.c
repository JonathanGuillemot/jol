#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"
#include "tools.h"
#include "jstr.h"
#include "stringarray.h"

/* MAIN */
int main (int argc, char ** argv) {
	
	tools_memory_init ();
	jstr j1 = regstr_to_jstr ("dromadaire");
	jstr j2 = regstr_to_jstr ("lesbienne");
	jstr j3 = regstr_to_jstr ("truite");
	jstr j4 = regstr_to_jstr ("filou");
	jstr j5 = regstr_to_jstr ("vespa");
	jstr j6 = regstr_to_jstr ("druide");
	jstr j7 = regstr_to_jstr ("chene");
	jstr j8 = regstr_to_jstr ("proposition");
	jstr j9 = regstr_to_jstr ("serpent");
	jstr j10 = regstr_to_jstr ("effet");
	jstr j11 = regstr_to_jstr ("venin");
	stringarray s1 = standard_empty_stringarray_create ();
	stringarray_add (s1, j1 );	
	stringarray_add (s1, j2 );	
	stringarray_add (s1, j3 );	
	stringarray_add (s1, j4 );	
	stringarray_add (s1, j5 );	
	stringarray_add (s1, j6 );	
	stringarray_add (s1, j7 );	
	stringarray_add (s1, j8 );	
	stringarray_add (s1, j9 );	
	stringarray_add (s1, j10 );	
	stringarray_add (s1, j11 );
	stringarray_debug (s1);
	stringarray_sort1 (s1);
	stringarray_debug (s1);
	hard_stringarray_destroy(s1);
	tools_memory_check_at_end_of_app ();

	return EXIT_SUCCESS;
}
