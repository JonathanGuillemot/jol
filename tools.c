#include "tools.h"
#include "intarray.h"


int string_to_int (char * str) {
	int ok;
	int n = safe_string_to_int (str, &ok);
	if (!ok)
	       printf("La chaine \"%s\" n'est pas numerique\n", str);
	return n;	
}

/* ok vaut 1 si uniquement alphanumerique
 * ok vaut 0 sinon
 */
int safe_string_to_int (char * str , int * ok) {
	if (*str == '-')
		return - safe_string_to_int (str + 1, ok);
	* ok = 1;
	if (! * str) {
		* ok = 0;
		return 0 ;
	}
	int r = 0;
	while (* str) {
		if ((* str < '0') || (* str > '9')) {
			* ok = 0;
		}
		r*= 10;
		r += (int) * str - 48;
		* str ++;
	}
	return r;
}

void int_swap (int * m, int * n) {
	int tmp  = * m;
	* m = * n;
	* n = tmp;
}

void char_swap (char * m, char * n) {
	char tmp  = * m;
	* m = * n;
	* n = tmp;
}

void tools_memory_init (void) {
	GLOBAL_ALLOC_MEMORY = 0;
}

void * tools_malloc (int alloc) {
	void * ptr = malloc (alloc);
	GLOBAL_ALLOC_MEMORY += alloc;
	return ptr;	
}

void tools_free (void * ptr, int alloc) {
	free (ptr);
	GLOBAL_ALLOC_MEMORY -= alloc;
}

void tools_memory_check_at_end_of_app (void) {
	if (GLOBAL_ALLOC_MEMORY != 0)
		printf("Attention fuite de memoire ! %d octets non liberes\n", GLOBAL_ALLOC_MEMORY);	
}

float puiss_iter (float a, int n) {
	int i;
	float r = 1;
	if (n < 0)
		return 1 / puiss_iter (a, -n);
	for (i = 1; i <= n; i++) 
		r *= a;
	return r;
}

float puiss_rec (float a, int n) {
	if (n < 0) return 1 / puiss_rec (a, -n);
	if (n==0) return 1;
	return a * puiss_rec (a, n-1);
}	

float puiss_alex (float a, int n) {
	if (n < 0) return 1 / puiss_alex (a, -n);
	if (n == 0) return 1;
	if ((n % 2) == 0) return puiss_alex (a * a, n/2);
	return a * puiss_alex (a * a, (n-1) / 2); 
}

int tools_random_int (int vmin, int vmax) {
	int amp = vmax - vmin + 1;
	double _alea = (1.0 * rand() / INT_MAX) * amp;
	int alea = (int) (vmin + _alea);
	if (alea < vmin) alea = vmin;
	else if (alea > vmax) alea = vmax;
	return alea;
}

void int_normalize_and_warn (int* n, int minv, int maxv) {
	if (*n < minv) {
		fprintf(stderr, "int %d normalized to %d.\n", *n, minv);
		*n = minv;
	}
	else if (*n > maxv) {
		fprintf(stderr, "int %d normalized to %d.\n", *n, maxv);
		*n = maxv;
	}
}

void int_normalize (int* n, int minv, int maxv) {
	if (*n < minv)
		*n = minv;
	else if (*n > maxv)
		*n = maxv;
}

int get_int (int minv, int maxv) {
	int n;
	scanf ("%d", &n);
	while ((n < minv) || (n > maxv)) {
		fprintf (stderr, "min = %d ; max = %d. Recommencez : ", minv, maxv);	
		scanf ("%d", &n);
	}
	return n;
}


char * regstr_clone (char * str) {
	int len = strlen (str);
	char * clone = (char*) tools_malloc (sizeof (char) * (len + 1));
	int i;
	for (i=0; i < len; i ++) 
		clone [i] = str[i];
	clone[i] = '\0';
	return clone;
}

void regstr_destroy (char ** sstr) {
	regstr_destroy_of_len (sstr, strlen (*sstr));
}

void regstr_destroy_of_len (char** sstr, int len) {
	char* str = *sstr;
	tools_free (str, sizeof (char) * (len + 1));
	*sstr = NULL;
}

bool regstr_equal (char * str1, char * str2) {
	int i = 0;
	while ((str1[i] != '\0') || (str2[i] != '\0')) {
		if (str1[i] != str2[i])
			return FALSE;
		i++;
	}
	return str1[i] == str2[i];
}
