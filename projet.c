#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	if (argc < 2) {

		char* ok = "Syntaxe correcte ./projet '[-u] palyndrome'\n";
		write(1, ok, strlen(ok));
		exit(0);
	}
	int fp[2];/*  ouverture d'un pipe */
	if (pipe(fp)) {//Si pas bon erreur
		write(2, "Error1", 6);
		exit(3);
	}
	switch (fork()) {
		case -1: /* erreur */
			write(2, "Error2", 6);
			exit(-1);
		case 0: /* FILS: execute la commande  palin*/
				 /* la sortie standard du processus est redirigee sur le pipe*/
			close(STDOUT_FILENO);
			dup(fp[1]); /* fp[1] sortie standard du processus */
			close(fp[1]);
			close(fp[0]); /* le processus ne lit pas dans le pipe */
			execlp("ps","ps","-e");/**/
			write(2, "Error3\n", 6);
			exit(3);
		default: /*El PADRE: pere execute la commande wc -l */
			   /* l'entree standard du processus est redirigee sur le pipe */
			close(STDIN_FILENO);
			dup(fp[0]); /* fp[1] sortie standard du processus */
			close(fp[0]);
			close(fp[1]);
			execlp("wc","wc","-l");
			printf("Error 404\n");
			exit(2);
			
			return 0;
	}
}
