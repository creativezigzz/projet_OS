#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		char* ok = "Syntaxe correcte ./projet '-parametres palyndrome'\n";
		write(1, ok, strlen(ok));
		exit(0);
	}

	int fp[2];/*  ouverture d'un pipe */
	if (pipe(fp)) {//Si pas bon erreur
		write(2, "Impossible de creer le pipe.", 6);
		exit(3);
	}
	
	/*On construit le tableau d'argument que prend ./palin*/
	char* argo[argc + 1];
	argo[0] = "palin";
	for (int i = 1; i < argc; i++) {
		argo[i] = argv[i];
		//printf("%s\n",argo[i]); Verification new table
	}
	argo[argc] = NULL;

	switch (fork()) {
		case -1: /* erreur */
			write(2, "Impossible de creer le pipe.", 6);
			exit(-1);
		case 0: /* FILS: execute la commande ps -e */
				 /* la sortie standard du processus est redirigee sur le pipe*/
			close(STDOUT_FILENO);
			dup(fp[1]); /* fp[1] sortie standard du processus */
			close(fp[1]);
			close(fp[0]); /* le processus ne lit pas dans le pipe */
			execvp("./palin", argo);/**/
			write(2, "Impossible d'ex�cuter le programme 'palin'.\n", 6);
			exit(3);
		default: /*El PADRE: pere execute la commande wc -l */
			   /* l'entree standard du processus est redirigee sur le pipe */
			wait(NULL);
			close(STDIN_FILENO);
			dup(fp[0]); /* fp[1] sortie standard du processus */
			close(fp[0]);
			close(fp[1]);

			char bonjour[50];
			int bytes;
			if ((bytes = read(0, bonjour, 50)) == -1) {
				printf("Impossible de lire dans le pipe.\n");
				exit(2);
			}
			write(1, bonjour, bytes);
			printf("\n");
			return 0;
	}
}
