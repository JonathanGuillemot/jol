#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int GLOBAL_ALLOC_MEMORY;

/*############*/
/* TYPEDEF    */
/*############*/

typedef char * regstr;
typedef char bool;

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
float puiss_iter (float a, int n);
float puiss_alex (float a, int n);
float puiss_rec (float a, int n);
int tools_random_int (int vmin, int vmax);
void int_normalize_and_warn (int* n, int minv, int maxv);
void int_normalize (int* n, int minv, int maxv);
int get_int (int minv, int maxv); 
char * regstr_clone (char * str);
void regstr_destroy (char ** sstr); 
void regstr_destroy_of_len (char** sstr, int len);
bool regstr_equal (char * str1, char * str2);
#endif
