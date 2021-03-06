#include <stdio.h>
#include <stdlib.h>
#include "jstr.h"
#include "intarray.h"
#include "tools.h"

  /*************/
 /* FONCTIONS */
/*************/

void jstr_create_aux (jstr string) {
	int i;
	if (string->alloc <= 0) {
		string->alloc = 4;
		printf ("jstr_create_aux : taille allouee negative ou nulle\n");
		printf ("une taille de 4 a ete allouee a la place\n");
	}
	string->data = tools_malloc(sizeof(char) * string->alloc);
	for (i = 0; i < string->alloc; i++)
		string->data[i] = '\0';
}

jstr jstr_create (int len) {
	jstr string = tools_malloc (sizeof (S_jstr));
	string->len = len;
	string->alloc = len;
	jstr_create_aux (string);
	return string;
}

jstr standard_empty_jstr_create (void) {
	return empty_jstr_create (JSTR_DEFAULT_ALLOC);
}

jstr empty_jstr_create (int alloc) {
	jstr string = tools_malloc (sizeof (S_jstr));
	string->len = 0;
	string->alloc = alloc;
	jstr_create_aux (string);
	return string;
}

jstr regstr_to_jstr (char * str) {
	jstr string = standard_empty_jstr_create ();
	int i;
	for (i=0; str[i] != '\0'; i++)
		jstr_add (string, str[i]);
	return string;		
}

char * jstr_to_regstr (jstr string) {
	char * str = tools_malloc (sizeof (char) * string->len + 1);
	int i;
	for (i=0; i < string->len; i++)
		str[i] = string->data[i];
	str[string->len] = '\0';
	return str;
}

void jstr_debug (jstr string) {
	int i;
	for (i=0; i < string->len ; i++)
		printf("%c",string->data[i]);
}

void ext_jstr_debug (jstr string) {
	printf("Allocation de la chaine = %d // Longueur de la chaine = %d\n", string->alloc, string->len);
	jstr_debug(string);
}

int jstr_search (jstr string , char c) {
	int i;
	for (i=0 ; i < string->len ; i++)
		if (string->data[i] == c) 
			return 1;
	return 0;
}

int jstr_count_occurence (jstr string, char c) {
	int i, n = 0;
	for (i=0; i < string->len; i++) {
		if (c == string->data[i])
			n++;
	}
	return n;
}

void jstr_destroy (jstr string) {
	tools_free (string->data, sizeof(char) * string->alloc);
	tools_free (string, sizeof(S_jstr));
}

void regular_jstr_destroy (jstr * string) {
	if (string == NULL) {
		printf ("regular_jstr_destroy : jstr is a NULL pointer.\n");
		return;
	}
	if (* string != NULL) {
		jstr_destroy (* string);
		* string = NULL;
	}
}

char jstr_get (jstr string, int index) {
	if ((index < 0) || (index >= string->len)) {
		printf("jstr_get : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d.\n", string->len-1);
		return -1;
	}
	return string->data[index];
}

void jstr_set (jstr string, int index, char c) {
	if ((index < 0) || (index >= string->len)) {
		printf("jstr_set : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d.\n", string->len-1);
		return;
	}
	string->data[index] = c;
}

void jstr_resize (jstr string, int newalloc) {
	char * newdata = tools_malloc (sizeof(char) * newalloc);
	int i;
	for (i=0; i < string->len; i++)
		newdata[i] = string->data[i];
	tools_free (string->data, sizeof(char) * string->alloc);
	string->data = newdata;
	string->alloc = newalloc;
}

void ext_jstr_set (jstr string, int index, char c) {
	if (index < 0) {
		printf("ext_jstr_set : index negatif impossible\n");
		return;
	}

	if (index < string->len) {
		string->data[index] = c;
		return;
	}	

	if (index > string->alloc-1) 
		jstr_resize (string, 2*index+1);
	
	int i;
	for (i=string->len; i < index; i++)
		string->data[i] = 0;

	string->data[index] = c;
	
	if (index > string->len-1) {
		string->len = index + 1;
	} 
}

int jstr_length (jstr string) {
	return string->len;
}

jstr jstr_concat (jstr T1, jstr T2) {
	jstr string = jstr_create (T1->len + T2->len);
	int i, j = 0;
	for (i = 0; i<T1->len; i++, j++)
		string->data[j] = T1->data[i];
	for (i = 0; i<T2->len; i++, j++)
		string->data[j] = T2->data[i];
	return string;
}

void D_jstr_concat (jstr S1, jstr S2) {
	int i;
	for (i=0; i < S2->len; i++)
		jstr_add (S1, S2->data[i]);
}

char jstr_get_min (jstr string) {
	return string->data[jstr_get_index_of_min(string)];
}

char jstr_get_max (jstr string) {
	return string->data[jstr_get_index_of_max(string)];
}

int jstr_get_index_of_min (jstr string) {
	return jstr_get_index_of_min_from (string, 0);
}

int jstr_get_index_of_max (jstr string) {
	return jstr_get_index_of_max_from (string, 0);
}

int jstr_get_index_of_min_from (jstr string, int n) {
	int i;
	char min=string->data[n];
	int index_mini = n;
	
	if ((n < 0) || (n >= string->len)) {
		printf("jstr_get_index_of_min_from : Hors limites du tableau\n");
		printf("les valeurs valides sont entre 0 et %d\n", string->len-1);
		return 0;
	}	

	for (i=n+1; i < string->len; i++) {
		if (min > string->data[i]) {
			min = string->data[i];
			index_mini = i;
		}	
	}
	return index_mini;
}

int jstr_get_index_of_max_from (jstr string, int n) {
	int i;
	char max=string->data[n];
	int index_maxi = n;
	
	if ((n < 0) || (n >= string->len)) {
		printf("jstr_get_index_of_max_from : Hors limites du tableau\n");
		printf("les valeurs valides sont entre 0 et %d\n", string->len-1);
		return 0;
	}	

	for (i=n+1; i < string->len; i++) {
		if (max < string->data[i]) {
			max = string->data[i];
			index_maxi = i;
		}	
	}
	return index_maxi;
}

void jstr_sort1 (jstr string) {
	int i;
	for (i=0; i < string->len - 1; i++) {
		char_swap (string->data + i , string->data + jstr_get_index_of_min_from (string, i));
	}
}

int jstr_sum (jstr string) {
	int i, sum = 0;
	for (i=0; i < string->len; i++) {
		sum += ((int) string->data[i]);
	}
	if (string->len <= 0) {
		printf("jstr_sum : tableau de longueur <= 0\n");
		return -1;
	}
	return sum;
}


float jstr_average (jstr string) {
	if (string->len > 0)
		return (jstr_sum (string) + 0.0) / string->len;
	else {
		printf("jstr_average : tableau de longueur <=0\n");
		return -1.0;
	}
}

float jstr_median (jstr string) {
	if (string->len <= 0) {
		printf("jstr_sum : tableau de longueur <= 0\n");
		return -1.0;
	}
	jstr copy = jstr_clone (string);
	float median;
	jstr_sort1(copy);
	if (copy->len % 2 == 0)
	 	median = ((int)copy->data[copy->len/2-1] + copy->data[copy->len/2])/2.0;
	else
		median = (int)copy->data[(copy->len-1)/2];
	
	jstr_destroy(copy);
	return median;
}

jstr jstr_clone (jstr string) {
	int i;
	jstr copy = jstr_create (string->len);
	for (i=0; i < string->len; i++)
		copy->data[i] = string->data[i];
	return copy;
}

void jstr_delete_sorted (jstr  string, int index) {

	if ((index < 0) || (index >= string->len)) {
	printf("jstr_get_index_of_min_from : Hors limites du tableau\n");
	printf("les valeurs valides sont entre 0 et %d\n", string->len-1);
	return;
	}

	int i;
	for (i = index + 1; i < string->len; i++)
		string->data[i-1] = string->data[i];
	
	string->len --;
}

void jstr_delete_unsorted (jstr  string, int index) {
	
	if ((index < 0) || (index >= string->len)) {
		printf("jstr_get_index_of_min_from : Hors limites du tableau\n");
		printf("les valeurs valides sont entre 0 et %d\n", string->len-1);
		return;
	}

	string->data[index] = string->data[string->len-1];
	string->len --;
}

void jstr_add (jstr  string, char c) {
	ext_jstr_set (string, string->len, c);
}


int jstr_equal_substr (jstr j1, int s1, int e1, jstr j2, int s2) {
	int i;
	if (s1 > s2) {
		int_swap (&s1, &s2);
		printf ("jstr_equal_substr : s1 > s2. Les valeurs ont ete changee automatiquement\n");
	}
	
	if ((s1 < 0) || (s2 < 0) || (s1 >= j1->len) || (e1 >= j1->len) || (s2 >= j2->len)) {
		printf("jstr_equal_substr : out of bounds\n");
		return 0;
	}

	if ((s2 + e1 - s1 + 1) > j2->len)
		return 0;
	for (i=s1; i <= e1; i++) {
		if (j1->data[i] != j2->data[s2])
			return 0;
		s2 ++;
	}
	return 1;
}

int jstr_equal (jstr j1, jstr j2) {
	if (j1->len != j2->len)
		return 0;
	return jstr_equal_substr (j1, 0, j1->len-1, j2, 0);
}

intarray jstr_find_substr_indices (jstr j, jstr sub) {
	int i;
	intarray array = standard_empty_intarray_create ();
	for (i=0; i <= j->len - sub->len; i++) {
		if (jstr_equal_substr (j, i, i + sub->len-1, sub, 0))
			intarray_add (array, i);
	}
	return array;
}

intarray jstr_find_proper_substr_indices (jstr j, jstr sub) {
	int i;
	intarray array = standard_empty_intarray_create ();
	for (i=0; i <= j->len - sub->len; i++) {
		if (jstr_equal_substr (j, i, i + sub->len-1, sub, 0))
			intarray_add (array, i);
			i += sub->len-1;
	}
	return array;
}

int jstr_compare (jstr j1, jstr j2) {
	
	int i, len_min;
	if (j1->len > j2->len)
		len_min = j2->len;
	else len_min = j1->len;

	for (i=0; i<len_min; i++) {
		if (j1->data[i] < j2->data[i])
			return -1;
		if (j1->data[i] > j2->data[i])
			return 1;
	}

	if (j1->len == j2->len) return 0;
	else if (j1->len > j2->len) return 1;
	else return -1;
}

jstr jstr_input (void) {
	jstr j = standard_empty_jstr_create ();
	char c = getchar ();
	while (c != '\n') {
		jstr_add (j, c);
		c = getchar ();
	}
	return j;
}

char* regstr_input (void){
	jstr j = jstr_input ();
	char* str = jstr_to_regstr (j);
	jstr_destroy (j);
	return str;
}


void jstr_reverse (jstr j) {
	if (j->len <= 1) return;
	int last = (j->len - 2) / 2;
	int i;
	for (i=0; i <= last; i++)
		char_swap (j->data +i, j->data + (j->len - 1 - i));

}

jstr int_to_jstr (int n) {
	jstr j = standard_empty_jstr_create ();
	if (n==0) {
		jstr_add (j, '0');
		return j;
	}
	while (n!=0) {
		jstr_add (j, '0' + n % 10);
		n/=10;
	}
	jstr_reverse (j);
	return j;
}

char * int_to_regstr (int n) {
	jstr j = int_to_jstr (n);
	char * str = jstr_to_regstr (j);
	jstr_destroy (j);	
	return str;
}
