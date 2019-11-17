#include <stdio.h>
#include <stdlib.h>
#include "tools.h"


int main (int * argc, char * argv) {
	printf("%d\n", string_to_int("986"));
	return EXIT_SUCCESS;
}

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
