#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//ps -e | wc -l
int main(int argc, char *argv[]){
  int fp[2];/*  ouverture d'un pipe */
  if( pipe(fp)){//Si pas bon erreur
    write(2,"Error1",6);
    exit(3);
  }
  switch (fork()) {
    case -1 : /* erreur */
              write(2,"Error2",6);
              exit(-1);
    case 0 : /* FILS: execute la commande ps -e */
             /* la sortie standard du processus est redirigee sur le pipe*/
            close (STDOUT_FILENO);
            dup(fp[1]); /* fp[1] sortie standard du processus */
             close (fp[1]);
             close (fp[0]); /* le processus ne lit pas dans le pipe */
             write(1,"OK",2);
             execlp ("palin", "palin", argv[1], NULL);
             write(2,"Error3",6);
             exit(3);
    default : /*El PADRE: pere execute la commande wc -l */
           /* l'entree standard du processus est redirigee sur le pipe */
           close (STDIN_FILENO);
           dup(fp[0]); /* fp[1] sortie standard du processus */
           close (fp[0]);
           close (fp[1]);
           write(1,"OK\n",3);
           execlp ("wc", "wc", "-l", NULL);
           write(2,"Error4",6);
           exit(-1);
         }
       }
