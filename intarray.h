#ifndef __INTARRAY_H__
#define __INTARRAY_H__
#include "tools.h"

#define INTARRAY_DEFAULT_ALLOC 8

/* PROTOTYPES */
intarray intarray_create (int len);
intarray empty_intarray_create (int alloc);
intarray standard_empty_intarray_create (void); 
void intarray_debug (intarray array);
void ext_intarray_debug (intarray array);
void intarray_print_positive_value (intarray array);
int intarray_search (intarray array , int n);
int intarray_count_occurence (intarray array, int n);
void intarray_destroy (intarray array);
int intarray_get (intarray array, int index);
void intarray_set (intarray array, int index, int n);
void ext_intarray_set (intarray array, int index, int n);
void intarray_add (intarray  array, int n);
void intarray_delete_sorted (intarray  array, int index);
void intarray_delete_unsorted (intarray  array, int index);
int intarray_length (intarray array);
intarray intarray_concat (intarray T1, intarray T2);
int intarray_get_min (intarray array);
int intarray_get_max (intarray array);
int intarray_get_index_of_min (intarray array);
int intarray_get_index_of_max (intarray array);
int intarray_get_index_of_min_from (intarray array, int n);
int intarray_get_index_of_max_from (intarray array, int n);
void intarray_sort1 (intarray array);
int intarray_sum (intarray array);
float intarray_average (intarray array);
float intarray_median (intarray array);
intarray intarray_clone (intarray array);

#endif
