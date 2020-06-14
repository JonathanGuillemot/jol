#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "intarray.h"
#include "tools.h"
#include "jstr.h"
#include "stringarray.h"
#include "charray2D.h"
#include "file.h"

int main (int argc, char ** argv) {
	tools_memory_init ();

	charray A = charray_load ("charray01.cha");
	if (A != NULL) {
		charray_debug (A);
		charray_destroy (&A);
	}
	tools_memory_check_at_end_of_app ();

	return EXIT_SUCCESS;
}
