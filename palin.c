#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Retourne la somme de la longueur des chaines de caractères d'un tableau.
int get_total_length(char* arr[], int size) {
	int i, length = 0;

	// On parcourt toute la table
	for (i = 0; i < size; i++)
		length += strlen(arr[i]); // On ajoute la longueur de la chaine

	// Et on retourne 
	return length;
}


void concat(char* arr[], int size, char* result) {
	int len, i, j, ci = 0;

	for (i = 0; i < size; i++) {
		len = strlen(arr[i]);
		for (j = 0; j < len; j++)
			result[ci++] = arr[i][j];

		result[ci++] = ' ';
	}

	result[ci] = '\0'; // on remplace l'espace de fin par la fin de la chaine
}


int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Utilisation: palin <chaine de caractères>\n");
		return 1;
	}

	int i;
	int length = get_total_length(&argv[1], argc - 1) + argc - 2;
	char* chaine = malloc(length);

	concat(&argv[1], argc - 1, chaine);

	for (i = 0; i < length / 2; i++) {
		if (chaine[i] != chaine[length - i - 1]) {
			printf("0\n");
			free(chaine);
			return 0;
		}
	}
	printf("1\n");
	free(chaine);

	return 0;
}
