#include <stdio.h>
#include <stdlib.h>

typedef struct _intarray intarray;

struct _intarray {
	int * data ;
	int len;
};



/* PROTOTYPES */
intarray intarray_create (int len);
void intarray_debug (intarray array);
void intarray_print_positive_value (intarray array);
int intarray_search (intarray array , int n);
int intarray_count_occurence (intarray array, int n);
void intarray_destroy (intarray array);
int intarray_get (intarray array, int index);
void intarray_set (intarray array, int index, int n);
int intarray_length (intarray array);

/* MAIN */
int main (int argc, char ** argv) {
	
	intarray t = intarray_create (8);
	intarray_set(t, 1, 123);
	intarray_set(t, 6, 406);
	intarray_set(t, 7, 65);
	printf("Index 7 = %d\n", intarray_get (t, 7));
	printf("Longueur du tableau = %d\n", intarray_length(t));
	intarray_debug (t);
	intarray_destroy (t);
	return EXIT_SUCCESS;
}


/* FONCTIONS */

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
