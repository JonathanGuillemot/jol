#include <stdio.h>
#include<stdlib.h>


int length (char * string) {
	int n = 0;
	while (string[n]) 
		n++;
	return n;
}

void upperstring (char * string) {
	int i = 0;
	while (string[i]) {
		if ((int)string[i] > 96 && (int)string[i] < 123)
			string[i] -= 32;
		i++;
	}	
}

void initialisation (char * string, char * wordtofind, int len, char c) {
	int i;
	for (i=1; i < len-1; i++)
		string[i] = c;
	string[len] = '\0';
	string[0] = wordtofind[0];
	string[len-1] = wordtofind[len-1];
}

void word_debug (char * string, char * wordtofind) {
	int i = 0;
	printf ("\nMot a trouver :\n\n");
	while (string[i]) {
		if ((int)wordtofind[i] < 65 || (int)wordtofind[i] > 90)
			printf("%c ", wordtofind[i]);
		else
			printf ("%c ", string[i]);
		i++;
	}
	printf("\n\n");
}

int change_char (char c, char * wordtofind, char * wordfinded) {
	int i = 0, f = 0;
	while (wordtofind[i]) {
		if (wordtofind[i] == c) {
			wordfinded[i] = c;
			f++;
		}
		i++;
	}
	return f;
}

int is_win (char * string, char c) {
	int i=0;
	while (string[i]) {
		if (string[i] == c) {
			return 0;
		}
		i++;
	}
	return 1;
}

int main (int argv, char ** argc) {
	
	char * wordtofind = argc[1];
	upperstring(wordtofind);
	int len = length (wordtofind);
	char wordfinded[len];
	char lettre = '\0';
	char buffer[2];
	char masque = '-';
	int life = 3;
	int used[26] = {0};

	initialisation (wordfinded, wordtofind, len, masque);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	word_debug (wordfinded, wordtofind);
	int t=1;
	while (! is_win (wordfinded, masque) && life > 0) {
		printf("\n\n####TOURS %d####\n", t);
		printf("Il vous reste %d vies\n", life);
		while ((int)lettre < 65 || (int)lettre > 90 || used[(int)lettre-65]) {
			printf("\nEntrez une lettre : ");
			scanf("%s", &buffer);
			upperstring(buffer);
			lettre = buffer[0];
		}

		if (change_char (lettre, wordtofind, wordfinded) == 0)
			life --;
		word_debug (wordfinded, wordtofind);
		t++;
		printf("###############\n");
		used[(int)lettre-65] = 1;
		lettre = '\0';
	}

	if (is_win (wordfinded, masque))
		printf("C'est gagne, vous avez trouve le mot : %s\n\n", wordfinded);
	else printf("Perdu, il fallait trouver : %s\n\n", wordtofind);

	return EXIT_SUCCESS;
}
