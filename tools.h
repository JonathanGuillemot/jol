#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdio.h>
#include <stdlib.h>

int GLOBAL_ALLOC_MEMORY;

/*############*/
/* TYPEDEF */
/*############*/

typedef char * regstr;

/*############*/
/* FONCTIONS */
/*############*/

int string_to_int (char * str);

/* ok vaut 1 si uniquement alphanumerique
 * ok vaut 0 sinon
 */
int safe_string_to_int (char * str , int * ok);
void int_swap (int * m, int * n);
void char_swap (char * m, char * n);
void tools_memory_init (void);
void  * tools_malloc (int alloc);
void tools_free (void * ptr, int alloc);
void tools_memory_check_at_end_of_app (void);

#endif
