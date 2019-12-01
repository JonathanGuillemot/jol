#ifndef __STRINGARRAY_H__
#define __STRINGARRAY_H__
#include "tools.h"
#include "jstr.h"

#define JSTR_DEFAULT_ALLOC 8

typedef struct _stringarray S_stringarray;
typedef struct _stringarray * stringarray;

struct _stringarray {
	jstr * data ;
	int alloc;
	int len;
};

/* PROTOTYPES */
stringarray stringarray_create (int len);
stringarray empty_stringarray_create (int alloc);
stringarray standard_empty_stringarray_create (void);
void stringarray_debug (stringarray string);
void ext_stringarray_debug (stringarray string);
int stringarray_search (stringarray string , jstr j);
int stringarray_count_occurence (stringarray string, jstr j);
void soft_stringarray_destroy (stringarray string);
void hard_stringarray_destroy (stringarray string);
jstr stringarray_get (stringarray string, int index);
void stringarray_set (stringarray string, int index, jstr j);
void ext_stringarray_set (stringarray string, int index, jstr j);
void stringarray_add (stringarray  string, jstr j);
void stringarray_delete_sorted (stringarray  string, int index);
void stringarray_delete_unsorted (stringarray  string, int index);
int stringarray_length (stringarray string);
stringarray stringarray_concat (stringarray S1, stringarray S2);
void D_stringarray_concat (stringarray S1, stringarray S2);
jstr stringarray_get_min (stringarray string);
jstr stringarray_get_max (stringarray string);
int stringarray_get_index_of_min (stringarray string);
int stringarray_get_index_of_max (stringarray string);
int stringarray_get_index_of_min_from (stringarray string, int n);
int stringarray_get_index_of_max_from (stringarray string, int n);
void stringarray_sort1 (stringarray string);
stringarray stringarray_clone (stringarray string);
int stringarray_equal (stringarray j1, stringarray j2);

#endif

