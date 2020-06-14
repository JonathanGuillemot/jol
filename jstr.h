#ifndef __JSTR_H__
#define __JSTR_H__
#include "tools.h"
#include "intarray.h"

#define JSTR_DEFAULT_ALLOC 8

typedef struct _jstr S_jstr;
typedef struct _jstr * jstr;

struct _jstr {
	char * data ;
	int alloc;
	int len;
};

/* PROTOTYPES */
jstr jstr_create (int len);
jstr empty_jstr_create (int alloc);
jstr standard_empty_jstr_create (void);
jstr regstr_to_jstr (char * str);
char * jstr_to_regstr (jstr string);
void jstr_debug (jstr string);
void ext_jstr_debug (jstr string);
int jstr_search (jstr string , char c);
int jstr_count_occurence (jstr string, char c);
void jstr_destroy (jstr string);
void regular_jstr_destroy (jstr * string);
char jstr_get (jstr string, int index);
void jstr_set (jstr string, int index, char c);
void ext_jstr_set (jstr string, int index, char c);
void jstr_add (jstr  string, char c);
void jstr_delete_sorted (jstr  string, int index);
void jstr_delete_unsorted (jstr  string, int index);
int jstr_length (jstr string);
jstr jstr_concat (jstr S1, jstr S2);
void D_jstr_concat (jstr S1, jstr S2);
char jstr_get_min (jstr string);
char jstr_get_max (jstr string);
int jstr_get_index_of_min (jstr string);
int jstr_get_index_of_max (jstr string);
int jstr_get_index_of_min_from (jstr string, int n);
int jstr_get_index_of_max_from (jstr string, int n);
void jstr_sort1 (jstr string);
int jstr_sum (jstr string);
float jstr_average (jstr string);
float jstr_median (jstr string);
jstr jstr_clone (jstr string);
int jstr_equal_substr (jstr j1, int s1, int e1, jstr j2, int s2);
int jstr_equal (jstr j1, jstr j2);
intarray jstr_find_substr_indices (jstr j, jstr sub);
intarray jstr_find_proper_substr_indices (jstr j, jstr sub);
int jstr_compare (jstr j1, jstr j2);
jstr jstr_input (void);
char* regstr_input (void);
void jstr_reverse (jstr j);
jstr int_to_jstr (int n);
char * int_to_regstr (int n);

#endif

