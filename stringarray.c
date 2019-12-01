#include <stdio.h>
#include <stdlib.h>
#include "stringarray.h"
#include "jstr.h"
#include "tools.h"

  /*************/
 /* FONCTIONS */
/*************/

void stringarray_create_aux (stringarray string) {
	int i;
	if (string->alloc <= 0) {
		string->alloc = 4;
		printf ("stringarray_create_aux : taille allouee negative ou nulle\n");
		printf ("une taille de 4 a ete allouee a la place\n");
	}
	string->data = tools_malloc(sizeof(jstr) * string->alloc);
	for (i = 0; i < string->alloc; i++)
		string->data[i] = NULL;
}

stringarray stringarray_create (int len) {
	stringarray string = tools_malloc (sizeof (S_stringarray));
	string->len = len;
	string->alloc = len;
	stringarray_create_aux (string);
	return string;
}

stringarray standard_empty_stringarray_create (void) {
	return empty_stringarray_create (JSTR_DEFAULT_ALLOC);
}

stringarray empty_stringarray_create (int alloc) {
	stringarray string = tools_malloc (sizeof (S_stringarray));
	string->len = 0;
	string->alloc = alloc;
	stringarray_create_aux (string);
	return string;
}

void stringarray_debug (stringarray string) {
	int i;
	for (i=0; i < string->len - 1 ; i++) {
		jstr_debug (string->data[i]);
		printf (" - ");
	}
	jstr_debug (string->data[string->len - 1]);
	printf("\n");
}

void ext_stringarray_debug (stringarray string) {
	printf("Allocation de la chaine = %d // Longueur de la chaine = %d\n", string->alloc, string->len);
	stringarray_debug(string);
}

int stringarray_search (stringarray string , jstr j) {
	int i;
	for (i=0 ; i < string->len ; i++)
		if (jstr_equal (string->data[i], j)) 
			return 1;
	return 0;
}

int stringarray_count_occurence (stringarray string, jstr j) {
	int i, n = 0;
	for (i=0; i < string->len; i++) {
		if (jstr_equal (string->data[i], j)) 
			n++;
	}
	return n;
}

void soft_stringarray_destroy (stringarray string) {
	tools_free (string->data, sizeof(jstr) * string->alloc);
	tools_free (string, sizeof(S_stringarray));
}

void hard_stringarray_destroy (stringarray string) {
	int i;
	for (i=0; i < string->len; i++)
		regular_jstr_destroy (string->data + i);
	soft_stringarray_destroy (string);
}

jstr stringarray_get (stringarray string, int index) {
	if ((index < 0) || (index >= string->len)) {
		printf("stringarray_get : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d.\n", string->len-1);
		return NULL;
	}
	return string->data[index];
}

void stringarray_set (stringarray string, int index, jstr j) {
	if ((index < 0) || (index >= string->len)) {
		printf("stringarray_set : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d.\n", string->len-1);
		return;
	}
	regular_jstr_destroy (string->data + index);
	string->data[index] = j;
}

void stringarray_resize (stringarray string, int newalloc) {
	jstr * newdata = tools_malloc (sizeof(jstr) * newalloc);
	int i;
	for (i=0; i < string->len; i++)
		newdata[i] = string->data[i];
	while (i < newalloc) {
		newdata[i] = NULL;
		i++;
	}
	tools_free (string->data, sizeof(jstr) * string->alloc);
	string->data = newdata;
	string->alloc = newalloc;
}

void ext_stringarray_set (stringarray string, int index, jstr j) {
	if (index < 0) {
		printf("ext_stringarray_set : index negatif impossible\n");
		return;
	}

	if (index < string->len) {
		regular_jstr_destroy (string->data + index);
		string->data[index] = j;
		return;
	}	

	if (index > string->alloc-1) 
		stringarray_resize (string, 2*index+1);
	
	int i;
	for (i=string->len; i < index; i++)
		string->data[i] = 0;

	string->data[index] = j;
	
	if (index > string->len-1) {
		string->len = index + 1;
	} 
}

int stringarray_length (stringarray string) {
	return string->len;
}

stringarray stringarray_concat (stringarray S1, stringarray S2) {
	stringarray string = stringarray_create (S1->len + S2->len);
	int i, j = 0;
	for (i = 0; i<S1->len; i++, j++)
		string->data[j] = jstr_clone (S1->data[i]);
	for (i = 0; i<S2->len; i++, j++)
		string->data[j] = jstr_clone (S2->data[i]);
	return string;
}

void D_stringarray_concat (stringarray S1, stringarray S2) {
	int i;
	for (i=0; i < S2->len; i++)
		stringarray_add (S1, jstr_clone(S2->data[i]));
}

jstr stringarray_get_min (stringarray string) {
	return string->data[stringarray_get_index_of_min(string)];
}

jstr stringarray_get_max (stringarray string) {
	return string->data[stringarray_get_index_of_max(string)];
}

int stringarray_get_index_of_min (stringarray string) {
	return stringarray_get_index_of_min_from (string, 0);
}

int stringarray_get_index_of_max (stringarray string) {
	return stringarray_get_index_of_max_from (string, 0);
}

int stringarray_get_index_of_min_from (stringarray string, int n) {
	int i;
	jstr min=string->data[n];
	int index_mini = n;
	
	if ((n < 0) || (n >= string->len)) {
		printf("stringarray_get_index_of_min_from : Hors limites du tableau\n");
		printf("les valeurs valides sont entre 0 et %d\n", string->len-1);
		return 0;
	}	

	for (i=n+1; i < string->len; i++) {
		if (jstr_compare (string->data[i], min) < 0) {
			min = string->data[i];
			index_mini = i;
		}	
	}
	return index_mini;
}

int stringarray_get_index_of_max_from (stringarray string, int n) {
	int i;
	jstr max=string->data[n];
	int index_maxi = n;
	
	if ((n < 0) || (n >= string->len)) {
		printf("stringarray_get_index_of_max_from : Hors limites du tableau\n");
		printf("les valeurs valides sont entre 0 et %d\n", string->len-1);
		return 0;
	}	

	for (i=n+1; i < string->len; i++) {
		if (jstr_compare (string->data[i], max) > 0) {
			max = string->data[i];
			index_maxi = i;
		}	
	}
	return index_maxi;
}

void stringarray_sort1 (stringarray string) {
	int i, index_min;
	jstr tmp;
	for (i=0; i < string->len - 1; i++) {
		index_min = stringarray_get_index_of_min_from (string, i);
		tmp = string->data[i];
		string->data[i] = string->data[index_min];
		string->data[index_min] = tmp;
	}
}

stringarray stringarray_clone (stringarray string) {
	int i;
	stringarray copy = stringarray_create (string->len);
	for (i=0; i < string->len; i++)
		copy->data[i] = string->data[i];
	return copy;
}

void stringarray_delete_sorted (stringarray  string, int index) {

	if ((index < 0) || (index >= string->len)) {
	printf("stringarray_get_index_of_min_from : Hors limites du tableau\n");
	printf("les valeurs valides sont entre 0 et %d\n", string->len-1);
	return;
	}
	regular_jstr_destroy (string->data + index);

	int i;
	for (i = index + 1; i < string->len; i++)
		string->data[i-1] = string->data[i];
	
	string->len --;
}

void stringarray_delete_unsorted (stringarray  string, int index) {
	
	if ((index < 0) || (index >= string->len)) {
		printf("stringarray_get_index_of_min_from : Hors limites du tableau\n");
		printf("les valeurs valides sont entre 0 et %d\n", string->len-1);
		return;
	}
	regular_jstr_destroy (string->data + index);
	string->data[index] = string->data[string->len-1];
	string->len --;
}

void stringarray_add (stringarray  string, jstr j) {
	ext_stringarray_set (string, string->len, j);
}


int stringarray_equal (stringarray s1, stringarray s2) {
	if (s1->len != s2->len)
		return 0;
	int i;
	for (i=0; i < s1->len; i++) {
		if (!(jstr_equal (s1->data[i], s2->data[i]))) 
			return 0;
	}
	return 1;
}

