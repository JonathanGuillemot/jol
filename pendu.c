#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _pendu S_pendu;
typedef struct _pendu * pendu;

struct _pendu {
	char * word;
	char tried[26];
	int remaining_letters;
	int remaining_tries;	
};

void S_pendu_init (pendu P, char * word, int nb_tries) {
	int len = strlen (word);
	char first = word[0], last = word[len - 1];
	int i;
	P->word = word;
	P->remaining_tries = nb_tries;
	P->remaining_letters = len;
	for (i=0; i < 26; i++) P->tried[i] = 0;
	if (len < 2) {
		P->remaining_letters = 0;
		return;
	}
	
	P->remaining_letters -= 2;
	
	if ((first >= 'A') && (first <= 'Z'))
		P->tried [first - 'A'] = 1;

	if ((last >= 'A') && (last <= 'Z'))
		P->tried [last - 'A'] = 1;

	for (i = 1; i < len-1; i++) {
		char c = word[i];
		if ((c == first) || (c == last) || (c < 'A') || (c > 'Z'))
			P->remaining_letters --;
	}
	//printf ("len = %d // word = %s // rem. letters = %d\n", len, word, P->remaining_letters);		
}

void string_uppercase (char * word) {
	int i;
	for (i = 0; word[i] != '\0'; i++) {
		if ((word[i] >= 'a') && (word[i] <= 'z'))
				word[i] -= ('a' - 'A');
	}
}

void pendu_display (pendu P) {
	int i;
	for (i = 0; P->word[i] != '\0'; i++) {
		char c = P->word[i];
		if ((P->tried[c - 'A'] == 1) || (c < 'A') || (c > 'Z'))
			printf ("%c", c);
		else printf ("-");
	}
	printf("\n");
}

char pendu_choice_letter (pendu P) {
	char c , ok = 0;
	char buffer[2];
	do {
		printf ("Choisi une lettre : ");
		scanf("%s",&buffer);
		c = buffer[0];
		if ((c >= 'a') && (c <= 'z'))
			c += ('A' - 'a');
		if ((c >= 'A') && (c <= 'Z') && (P->tried[c - 'A'] == 0))
			ok = 1;
		else 
			printf("%c n'est pas un caractere valide ou il a deja ete utilise\n", c); 

	}
	while (ok == 0);
	return c;
}

void pendu_play (pendu P) {
	while ((P->remaining_tries > 0) && (P->remaining_letters > 0)) {
		int i, find = 0;
		printf("Il vous reste %d vies\n", P->remaining_tries);
		pendu_display (P);
		char letter = pendu_choice_letter (P);
		P->tried[letter - 'A'] = 1;
		for (i=0; P->word[i] != '\0'; i++) {
			if (P->word[i] == letter) {
				P->remaining_letters --;
				find = 1;
			}
		}
		if (find == 0)
			P->remaining_tries--;
	}

	if (P->remaining_letters == 0) {
		
		pendu_display (P);
		printf ("Vous avez gagne\n");

	} else {

		printf("Vous avez perdu\n");
		printf("Le mot a trouver etait : %s\n", P->word);

	}
}

int main (int argc, char ** argv) {
	int i;
	S_pendu P;

	char  * word; int nb_tries;
	char default_word[] = "saperloppe";
	if (argc > 1) word = argv[1];
	else word = default_word;

	if (argc > 2) nb_tries = atoi (argv[2]);
	else nb_tries = 7;
	
	for (i=0; i < 75; i++) printf("\n");

	printf ("Jeu du pendu. Vous avez %d essais\n", nb_tries);

	string_uppercase (word);
	
	S_pendu_init (&P, word, nb_tries);

	pendu_play (&P);

	return EXIT_SUCCESS;
}
