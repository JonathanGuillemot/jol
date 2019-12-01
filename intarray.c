#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"
#include "tools.h"

  /*************/
 /* FONCTIONS */
/*************/

void intarray_create_aux (intarray array) {
	int i;
	if (array->alloc <= 0) {
		array->alloc = 4;
		printf ("intarray_create_aux : taille allouee negative ou nulle\n");
		printf ("une taille de 4 a ete allouee a la place\n");
	}
	array->data = tools_malloc(sizeof(int) * array->alloc);
	for (i = 0; i < array->alloc; i++)
		array->data[i] = 0;
}

intarray intarray_create (int len) {
	intarray array = tools_malloc (sizeof (S_intarray));
	array->len = len;
	array->alloc = len;
	intarray_create_aux (array);
	return array;
}

intarray standard_empty_intarray_create (void) {
	return empty_intarray_create (INTARRAY_DEFAULT_ALLOC);
}

intarray empty_intarray_create (int alloc) {
	intarray array = tools_malloc (sizeof (S_intarray));
	array->len = 0;
	array->alloc = alloc;
	intarray_create_aux (array);
	return array;
}

void intarray_debug (intarray array) {
	int i;
	printf("[");
	for (i=0; i < array->len - 1 ; i++)
		printf(" %d ,",array->data[i]);
	if (array->len > 0)
		printf(" %d ", array->data[array->len-1]);
	printf("]\n");
}

void ext_intarray_debug (intarray array) {
	printf("Allocation du tableau = %d // Longueur du tableau = %d\n", array->alloc, array->len);
	intarray_debug(array);
}

void intarray_print_positive_value (intarray array) {
	int i;
	printf("[");
	for (i=0; i < array->len - 1; i++) {
		

		if (array->data[i]>=0 && i==array->len-2 && array->data[i+1] < 0 ) 
			printf(" %d ", array->data[i]);
		else if (array->data[i]>=0) 
			printf(" %d ,", array->data[i]);
	}
		if (array->data[array->len-1] >= 0)
		printf(" %d ", array->data[array->len-1]);
	printf("]\n");
}

int intarray_search (intarray array , int n) {
	int i;
	for (i=0 ; i < array->len ; i++)
		if (array->data[i] == n) 
			return 1;
	return 0;
}

int intarray_count_occurence (intarray array, int n) {
	int i, c = 0;
	for (i=0; i < array->len; i++) {
		if (n == array->data[i])
			c++;
	}
	return c;
}

void intarray_destroy (intarray array) {
	tools_free (array->data, sizeof(int) * array->alloc);
	tools_free (array, sizeof(S_intarray));
}

int intarray_get (intarray array, int index) {
	if ((index < 0) || (index >= array->len)) {
		printf("intarray_get : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d.\n", array->len-1);
		return -1;
	}
	return array->data[index];
}

void intarray_set (intarray array, int index, int n) {
	if ((index < 0) || (index >= array->len)) {
		printf("intarray_set : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d.\n", array->len-1);
		return;
	}
	array->data[index] = n;
}

void intarray_resize (intarray array, int newalloc) {
	int * newdata = tools_malloc (sizeof(int) * newalloc);
	int i;
	for (i=0; i < array->len; i++)
		newdata[i] = array->data[i];
	tools_free (array->data, sizeof(int) * array->alloc);
	array->data = newdata;
	array->alloc = newalloc;
}

void ext_intarray_set (intarray array, int index, int n) {
	if (index < 0) {
		printf("ext_intarray_set : index negatif impossible\n");
		return;
	}

	if (index < array->len) {
		array->data[index] = n;
		return;
	}	

	if (index > array->alloc-1) 
		intarray_resize (array, 2*index+1);
	
	int i;
	for (i=array->len; i < index; i++)
		array->data[i] = 0;

	array->data[index] = n;
	
	if (index > array->len-1) {
		array->len = index + 1;
	} 
}

int intarray_length (intarray array) {
	return array->len;
}

intarray intarray_concat (intarray T1, intarray T2) {
	intarray array = intarray_create (T1->len + T2->len);
	int i = 0, j = 0;
	for (;i<T1->len; i++, j++)
		array->data[j] = T1->data[i];
	for (i=0; i<T2->len; i++, j++)
		array->data[j] = T2->data[i];
	return array;
}

int intarray_get_min (intarray array) {
	return array->data[intarray_get_index_of_min(array)];
}

int intarray_get_max (intarray array) {
	return array->data[intarray_get_index_of_max(array)];
}

int intarray_get_index_of_min (intarray array) {
	return intarray_get_index_of_min_from (array, 0);
}

int intarray_get_index_of_max (intarray array) {
	return intarray_get_index_of_max_from (array, 0);
}

int intarray_get_index_of_min_from (intarray array, int n) {
	int i, min=array->data[n], index_mini = n;
	
	if ((n < 0) || (n >= array->len)) {
		printf("intarray_get_index_of_min_from : Hors limites du tableau\n");
		printf("les valeurs valides sont entre 0 et %d\n", array->len-1);
		return 0;
	}	

	for (i=n+1; i < array->len; i++) {
		if (min > array->data[i]) {
			min = array->data[i];
			index_mini = i;
		}	
	}
	return index_mini;
}

int intarray_get_index_of_max_from (intarray array, int n) {
	int i, max=array->data[n], index_maxi = n;
	
	if ((n < 0) || (n >= array->len)) {
		printf("intarray_get_index_of_max_from : Hors limites du tableau\n");
		printf("les valeurs valides sont entre 0 et %d\n", array->len-1);
		return 0;
	}	

	for (i=n+1; i < array->len; i++) {
		if (max < array->data[i]) {
			max = array->data[i];
			index_maxi = i;
		}	
	}
	return index_maxi;
}

void intarray_sort1 (intarray array) {
	int i;
	for (i=0; i < array->len - 1; i++) {
		int_swap (array->data + i , array->data + intarray_get_index_of_min_from (array, i));
	}
}

int intarray_sum (intarray array) {
	int i, sum = 0;
	for (i=0; i < array->len; i++) {
		sum += array->data[i];
	}
	if (array->len <= 0) {
		printf("intarray_sum : tableau de longueur <= 0\n");
		return -1;
	}
	return sum;
}

float intarray_average (intarray array) {
	if (array->len > 0)
		return (intarray_sum (array) + 0.0) / array->len;
	else {
		printf("intarray_average : tableau de longueur <=0\n");
		return -1.0;
	}
}

float intarray_median (intarray array) {
	if (array->len <= 0) {
		printf("intarray_sum : tableau de longueur <= 0\n");
		return -1.0;
	}
	intarray copy = intarray_clone (array);
	float median;
	intarray_sort1(copy);
	if (copy->len % 2 == 0)
		median = (copy->data[copy->len/2-1] + copy->data[copy->len/2])/2.0;
	else
		median = copy->data[(copy->len-1)/2];
	
	intarray_destroy(copy);
	return median;
}

intarray intarray_clone (intarray array) {
	int i;
	intarray copy = intarray_create (array->len);
	for (i=0; i < array->len; i++)
		copy->data[i] = array->data[i];
	return copy;
}

void intarray_delete_sorted (intarray  array, int index) {

	if ((index < 0) || (index >= array->len)) {
	printf("intarray_get_index_of_min_from : Hors limites du tableau\n");
	printf("les valeurs valides sont entre 0 et %d\n", array->len-1);
	return;
	}

	int i;
	for (i = index + 1; i < array->len; i++)
		array->data[i-1] = array->data[i];
	
	array->len --;
}

void intarray_delete_unsorted (intarray  array, int index) {
	
	if ((index < 0) || (index >= array->len)) {
		printf("intarray_get_index_of_min_from : Hors limites du tableau\n");
		printf("les valeurs valides sont entre 0 et %d\n", array->len-1);
		return;
	}

	array->data[index] = array->data[array->len-1];
	array->len --;
}

void intarray_add (intarray  array, int n) {
	ext_intarray_set (array, array->len, n);
}

