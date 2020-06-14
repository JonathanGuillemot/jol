#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "charray2D.h"

typedef struct _morpion * morpion;

struct _morpion {
	charray grid;
	char player; // X ou O
	char status; // X si X gagne, O si O gagne, ? si nul, . sinon
	int nb_empty;
};

morpion morpion_init (void);
void morpion_destroy (morpion* MM);
void morpion_display (morpion M);
void morpion_play (morpion M);
void morpion_swap_player (morpion M);
void morpion_saisie (morpion M, int* i, int* j);
void morpion_end (morpion M); 
void morpion_tests (morpion M); 
