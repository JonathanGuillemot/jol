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
intarray intarray_concact (intarray T1, intarray T2);
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



