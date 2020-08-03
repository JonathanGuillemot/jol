#ifndef __KVDATA_H__
#define __KVDATA_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct _KVdata* KVdata;

struct _KVdata {
	stringarray KEYS;
	stringarray VALUES;
};
KVdata KVdata_load (char * filenamei, bool verbose);
void KVdata_destroy (KVdata* KV);
char* KVdata_get_string (KVdata KV, char* key);
void KVdata_get_int (KVdata KV, char* key, int* n, bool* found);
#endif
