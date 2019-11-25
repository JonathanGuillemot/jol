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
	printf ("len = %d // word = %s // rem. letters = %d\n", len, word, P->remaining_letters);		
}

void string_uppercase (char * word) {
	int i;
	for (i = 0; word[i] != '\0'; i++) {
		if ((word[i] >= 'a') && (word[i] <= 'z'))
				word[i] -= ('a' - 'A');
	}
}

int main (int argc, char ** argv) {

	S_pendu P;

	char  * word; int nb_tries;
	char default_word[] = "saperloppe";
	if (argc > 1) word = argv[1];
	else word = default_word;

	if (argc > 2) nb_tries = atoi (argv[2]);
	else nb_tries = 7;
	
	printf ("Jeu du pendu. Vous avez %d essais\n", nb_tries);

	string_uppercase (word);
	S_pendu_init (&P, word, nb_tries);


	return EXIT_SUCCESS;
}
