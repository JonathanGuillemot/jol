#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdio.h>
#include <stdlib.h>

typedef char * regstr;

int string_to_int (char * str);

/* ok vaut 1 si uniquement alphanumerique
 * ok vaut 0 sinon
 */
int safe_string_to_int (char * str , int * ok);
void int_swap (int * m, int * n);
void char_swap (char * m, char * n);


#endif
