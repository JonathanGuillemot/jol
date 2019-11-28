#ifndef __JSTR_H__
#define __JSTR_H__
#include "tools.h"
#include "intarray.h"

typedef struct _jstr S_jstr;
typedef struct _jstr * jstr;

struct _jstr {
	char * data ;
	int alloc;
	int len;
};

#define JSTR_DEFAULT_ALLOC 8

/* PROTOTYPES */
jstr jstr_create (int len);
jstr empty_jstr_create (int alloc);
jstr standard_empty_jstr_create (void);
jstr regstr_to_jstr (char * str);
char * jstr_to_regstr (jstr string);
void jstr_debug (jstr string);
void ext_jstr_debug (jstr string);
void jstr_print_positive_value (jstr string);
int jstr_search (jstr string , char c);
int jstr_count_occurence (jstr string, char c);
void jstr_destroy (jstr string);
char jstr_get (jstr string, int index);
void jstr_set (jstr string, int index, char c);
void ext_jstr_set (jstr string, int index, char c);
void jstr_add (jstr  string, char c);
void jstr_delete_sorted (jstr  string, int index);
void jstr_delete_unsorted (jstr  string, int index);
int jstr_length (jstr string);
jstr jstr_concact (jstr S1, jstr S2);
void D_jstr_concact (jstr S1, jstr S2);
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



#endif

/*
 *    0) Concatener en une seule chaine tous les arguments argv sauf argv[0]
 *    1) int jstr_equal_substr (jstr j1, int s1, int e1, jstr j2, int s2);
 *    		=> retourne 1 si le motif de j1 commencant en s1 et finissant en e1 est egale au motif de j2 commencant en s2
 *    2) int jstr_equal (jstr j1, jstr j2);
 *    3)intarray jstr_find_substr_indices (jstr j, jstr sub)
 *    		=> retourne un intarray enregistrant toutes les positions de j ou la chaine sub commence (chevauchement possible)
 *
 *    4)intarray jstr_find_substr_indices (jstr j, jstr sub)
 *    		=> idem aue 3) mais sans chevauchement possible
 *    5)int jstr_compare (jstr j1, jstr j2,);
 *		-1 si j1 < j2 // 0 si j1 egale a j2 // 1 si j1 > J2 (ordre lexicographique)
 *
 */
