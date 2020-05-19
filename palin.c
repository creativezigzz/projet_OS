#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

// Retourne la somme de la longueur des chaines de caractères d'un tableau.
int get_total_length(char* arr[], int size) {
	int i, length = 0;

	// On parcourt toute la table
	for (i = 0; i < size; i++)
		length += strlen(arr[i]); // On ajoute la longueur de la chaine

	// Et on retourne 
	return length;
}

// Concatène un tableau de chaines de caractères avec des espaces
void concat(char* arr[], int size, char* result) {
	int len, i, j, ci = 0;

	// Pour chaque élément dans le tableau,
	for (i = 0; i < size; i++) {
		len = strlen(arr[i]);
		for (j = 0; j < len; j++)
			result[ci++] = arr[i][j]; // On ajoute au résultat toutes les lettres de l'élément

		result[ci++] = ' '; // A chaque fin de mot, on rajoute un espace
	}

	result[ci] = '\0'; // On remplace le dernier espace par la fin de la chaine
}


int main(int argc, char* argv[]) {
	char* help = "Utilisation: palin [-u] <chaine de caractères>\n";

	if (argc < 2) {
		write(1, help, strlen(help));
		return 1;
	}

	// Offset dans argv
	int i, j, offset = 1;

	if (strcmp(argv[offset], "-u") == 0) {
		if (argc < 3) {
			write(1, help, strlen(help));
			return 1;
		}

		// On incrémente l'offset par un
		for (i = ++offset; i < argc; i++)
			for (j = 0; j < (int) strlen(argv[i]); j++)
				argv[i][j] = toupper((int) argv[i][j]); // Et on convertit tous les cacractères en uppercase
	}

	// On récupère la longueur totale des arguments
	int length = get_total_length(&argv[offset], argc - offset) + argc - (1 + offset);
	char chaine[length]; // On alloue l'espace

	// On concatène dans la variable chaine
	concat(&argv[offset], argc - offset, chaine);

	for (i = 0; i < length / 2; i++) {
		if (chaine[i] != chaine[length - i - 1]) {
			write(1, "0", 2);
			return 0;
		}
	}
	write(1, "1", 2);

	return 0;
}
