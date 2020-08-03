#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "stringarray.h"
#include "KVdata.h"
#include "file.h"

/* private */
KVdata KVdata_alloc (void) {
	KVdata KV = (KVdata) tools_malloc (sizeof (struct _KVdata));
	KV->KEYS = standard_empty_stringarray_create ();
	KV->VALUES = standard_empty_stringarray_create ();
	return KV;
}

KVdata KVdata_load (char * filename, bool verbose) {
	KVdata KV = KVdata_alloc ();
	file F = file_open (filename, FILE_READ_ONLY);
	bool eof = FALSE;
	char* key; char* value;
	if (F == NULL) {
		fprintf (stderr, "KVdata_load : unable to open file %s.\n", filename);
		KVdata_destroy (&KV);
		return NULL;
	}
	while (!eof) {
		file_read_next_text_str (F, &key, &eof);
		if (!eof) {
			file_read_next_text_str (F, &value, &eof);
			if (eof) {
				fprintf(stderr, "No value found for key %s.\n", key);
				regstr_destroy (&key);
			}
			else {
				stringarray_add (KV->KEYS, regstr_to_jstr (key));
				stringarray_add (KV->VALUES, regstr_to_jstr (value));
				if (verbose)
					fprintf (stderr, "key = %s ; value = %s\n", key, value);
				regstr_destroy (&key);
				regstr_destroy (&value);
			}
		}
	}

	file_close (&F);
	return KV;
}

void KVdata_destroy (KVdata* KKV) {
	KVdata KV = *KKV;
	hard_stringarray_destroy (KV->KEYS);
	hard_stringarray_destroy (KV->VALUES);
	tools_free (KV, sizeof (struct _KVdata));
	*KKV = NULL;
}

char* KVdata_get_string (KVdata KV, char* key) {
	int i;
	for (i = 0; i < KV->KEYS->len; i++) {
		jstr j = stringarray_get (KV->KEYS, i);
		char* key2 = jstr_to_regstr (j);
		if (regstr_equal (key, key2)) {
			regstr_destroy (&key2);
			return jstr_to_regstr (stringarray_get (KV->VALUES, i));
		}
		regstr_destroy (&key2);
	}
	return NULL;
}
void KVdata_get_int (KVdata KV, char* key, int* n, bool* found) {
	char * str = KVdata_get_string (KV, key);
	if (str == NULL) {
		*n = -1;
		*found = FALSE;
		return;
	}
	int ok;
	*n = safe_string_to_int (str, &ok);
	regstr_destroy (&str);
	if (!ok) {
		*n = -1;
		*found = FALSE;
	} else
		*found = TRUE;
}
