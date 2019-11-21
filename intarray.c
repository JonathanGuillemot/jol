#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"
#include "tools.h"

  /*************/
 /* FONCTIONS */
/*************/

intarray intarray_create (int len) {
	intarray array;
	int i;
	array.len = len;
	array.data = malloc(sizeof(int) * len);
	
	for (i = 0; i < len; i++)
		array.data[i] = 0;

	return array;
}

void intarray_debug (intarray array) {
	int i;
	printf("[");
	for (i=0; i < array.len - 1 ; i++)
		printf(" %d ,",array.data[i]);
	printf(" %d ", array.data[array.len-1]);;
	printf("]\n");
}

void intarray_print_positive_value (intarray array) {
	int i;
	printf("[");
	for (i=0; i < array.len - 1; i++) {
		

		if (array.data[i]>=0 && i==array.len-2 && array.data[i+1] < 0 ) 
			printf(" %d ", array.data[i]);
		else if (array.data[i]>=0) 
			printf(" %d ,", array.data[i]);
	}
		if (array.data[array.len-1] >= 0)
		printf(" %d ", array.data[array.len-1]);
	printf("]\n");
}

int intarray_search (intarray array , int n) {
	int i;
	for (i=0 ; i < array.len ; i++)
		if (array.data[i] == n) 
			return 1;
	return 0;
}

int intarray_count_occurence (intarray array, int n) {
	int i, c = 0;
	for (i=0; i < array.len; i++) {
		if (n == array.data[i])
			c++;
	}
	return c;
}

void intarray_destroy (intarray array) {
	free(array.data);
}

int intarray_get (intarray array, int index) {
	if ((index < 0) || (index >= array.len)) {
		printf("intarray_get : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d.\n", array.len-1);
		return -1;
	}
	return array.data[index];
}

void intarray_set (intarray array, int index, int n) {
	if ((index < 0) || (index >= array.len)) {
		printf("intarray_set : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d.\n", array.len-1);
		return;
	}
	array.data[index] = n;
}

int intarray_length (intarray array) {
	return array.len;
}

intarray intarray_concact (intarray T1, intarray T2) {
	intarray array = intarray_create (T1.len + T2.len);
	int i = 0, j = 0;
	for (;i<T1.len; i++, j++)
		array.data[j] = T1.data[i];
	for (i=0; i<T2.len; i++, j++)
		array.data[j] = T2.data[i];
	return array;
}

int intarray_get_min (intarray array) {
	return array.data[intarray_get_index_of_min(array)];
}

int intarray_get_max (intarray array) {
	return array.data[intarray_get_index_of_max(array)];
}

int intarray_get_index_of_min (intarray array) {
	return intarray_get_index_of_min_from (array, 0);
}

int intarray_get_index_of_max (intarray array) {
	return intarray_get_index_of_max_from (array, 0);
}

int intarray_get_index_of_min_from (intarray array, int n) {
	int i, min=array.data[n], index_mini = n;
	
	if ((n < 0) || (n >= array.len)) {
		printf("intarray_get_index_of_min_from : Hors limites du tableau\n");
		printf("les valeurs valides sont entre 0 et %d\n", array.len-1);
		return 0;
	}	

	for (i=n+1; i < array.len; i++) {
		if (min > array.data[i]) {
			min = array.data[i];
			index_mini = i;
		}	
	}
	return index_mini;
}

int intarray_get_index_of_max_from (intarray array, int n) {
	int i, max=array.data[n], index_maxi = n;
	
	if ((n < 0) || (n >= array.len)) {
		printf("intarray_get_index_of_max_from : Hors limites du tableau\n");
		printf("les valeurs valides sont entre 0 et %d\n", array.len-1);
		return 0;
	}	

	for (i=n+1; i < array.len; i++) {
		if (max < array.data[i]) {
			max = array.data[i];
			index_maxi = i;
		}	
	}
	return index_maxi;
}

void intarray_sort1 (intarray array) {
	int i;
	for (i=0; i < array.len - 1; i++) {
		int_swap (array.data + i , array.data + intarray_get_index_of_min_from (array, i));
	}
}

int intarray_sum (intarray array) {
	int i, sum = 0;
	for (i=0; i < array.len; i++) {
		sum += array.data[i];
	}
	if (array.len <= 0) {
		printf("intarray_sum : tableau de longueur <= 0\n");
		return -1;
	}
	return sum;
}

float intarray_average (intarray array) {
	if (array.len > 0)
		return (intarray_sum (array) + 0.0) / array.len;
	else {
		printf("intarray_average : tableau de longueur <=0\n");
		return -1.0;
	}
}

float intarray_median (intarray array) {
	if (array.len <= 0) {
		printf("intarray_sum : tableau de longueur <= 0\n");
		return -1.0;
	}
	intarray copy = intarray_clone (array);
	float median;
	intarray_sort1(copy);
	if (copy.len % 2 == 0)
		median = (copy.data[copy.len/2-1] + copy.data[copy.len/2])/2.0;
	else
		median = copy.data[(copy.len-1)/2];
	
	intarray_destroy(copy);
	return median;
}

intarray intarray_clone (intarray array) {
	int i;
	intarray copy = intarray_create (array.len);
	for (i=0; i < array.len; i++)
		copy.data[i] = array.data[i];
	return copy;
}
