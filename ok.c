#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define NB_ENTIERS 5

/*
int pipe (int desc[2]);
int write (int desc, char * buffer, int longeur);
int read (int desc, char * buffer, int longeur);
int close (int desc);
int exec*
*/
int main(void){
  pid_t pid_fils;
  int fd[2];
  if(pipe(fd)!=0) {
    printf("Error pipe\n");
    exit(1);
}
  pid_fils =fork();

  if(pid_fils == 0){/* C'est le fils */
    char ok[100];
    close(fd[0]);//Fermeture pipe
    printf("Ecrivez un truc\n");
    scanf("%s",ok );
    while(strlen(ok) < 5){
      printf("Je suis ici (encore)\n");
      scanf("%s",ok );
    }

    write(fd[1],&ok,100);//Ecriture dans le pipe

    close(fd[1]);
    exit(0) ;
  }
  else{ //le padre
    wait(NULL);
    close (fd[1]);
    printf("fermeture \n");

    char ok[100];
    read(fd[0], &ok ,100);
    close(fd[0]);
    sleep(3);
    printf("%s a été lu \n",ok);
    exit(EXIT_SUCCESS);
  }

  exit(0);
}
