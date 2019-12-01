#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "intarray.h"


int string_to_int (char * str) {
	int ok;
	int n = safe_string_to_int (str, &ok);
	if (!ok)
	       printf("La chaine \"%s\" n'est pas numerique\n", str);
	return n;	
}

/* ok vaut 1 si uniquement alphanumerique
 * ok vaut 0 sinon
 */
int safe_string_to_int (char * str , int * ok) {
	if (*str == '-')
		return - safe_string_to_int (str + 1, ok);
	* ok = 1;
	if (! * str) {
		* ok = 0;
		return 0 ;
	}
	int r = 0;
	while (* str) {
		if ((* str < '0') || (* str > '9')) {
			* ok = 0;
		}
		r*= 10;
		r += (int) * str - 48;
		* str ++;
	}
	return r;
}

void int_swap (int * m, int * n) {
	int tmp  = * m;
	* m = * n;
	* n = tmp;
}

void char_swap (char * m, char * n) {
	char tmp  = * m;
	* m = * n;
	* n = tmp;
}

void tools_memory_init (void) {
	GLOBAL_ALLOC_MEMORY = 0;
}

void * tools_malloc (int alloc) {
	void * ptr = malloc (alloc);
	GLOBAL_ALLOC_MEMORY += alloc;
	return ptr;	
}

void tools_free (void * ptr, int alloc) {
	free (ptr);
	GLOBAL_ALLOC_MEMORY -= alloc;
}

void tools_memory_check_at_end_of_app (void) {
	if (GLOBAL_ALLOC_MEMORY != 0)
		printf("Attention fuite de memoire ! %d octets non liberes\n", GLOBAL_ALLOC_MEMORY);	
}
