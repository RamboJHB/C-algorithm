#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

/* On reprend l'exo 5 du TD1. On cree deux processus fils1 et fils2 qui a leur tour cree chacun un fils fils1.1 et fils2.1
   -Ces quatre processus ne font qu'imprimer leur pid et ppid.
   -fils2 imprime le pid de fils1.
   -Les processus qui ont des fils doivent attendre qu'ils se terminent pour terminer
   -fils 1.1 se termine apres fils2 et fils1.1
   -on utilise uniquement les signaux, pas de wait ou sleep*/

void sigusr_handler(){
  return;
}

int main(int argc, char* argv[]){
  pid_t pid_fork1, pid_fork2, pid_fils1 = 0;
  sigset_t mask;
  struct sigaction act_usr;
  int i = 0;

  act_usr.sa_flags = 0;
  act_usr.sa_handler = sigusr_handler;
  sigaction(SIGUSR1, &act_usr, NULL);
  sigaction(SIGUSR2, &act_usr, NULL);

  sigfillset(&mask);
  sigprocmask(SIG_SETMASK, &mask, NULL);

  for(i=0; i<2; i++){
    if((pid_fork1 = fork()) == -1 ){
      perror("Erreur de creation de fils");
      return errno;
    }
    else if(pid_fork1 == 0){
      if((pid_fork2 = fork()) == -1 ){
        perror("Erreur de creation de petit-fils");
        return errno;
      }
      else if(pid_fork2 == 0){
        printf("Infos du petit-fils %d:\n", i);
        printf("pid : %d\n", getpid());
        printf("ppid : %d\n", getppid());
        printf("Fin du petit-fils %d\n\n", i);
        kill(getppid(), SIGUSR2);
        exit(1);
      }
      else{
        sigdelset(&mask, SIGUSR2);
        sigsuspend(&mask);

        printf("Infos du fils %d:\n", i);
        printf("pid : %d\n", getpid());
        printf("ppid : %d\n", getppid());
        if(i == 1){
          printf("pid du frere : %d\n", pid_fils1);
        }

        if(i == 1){
          kill(getppid(), SIGUSR1);
          kill(pid_fils1, SIGUSR1);
          printf("Fin du fils %d\n\n", i);
          exit(1);
        }

        sigdelset(&mask, SIGUSR1);
        sigsuspend(&mask);
        printf("Fin du fils %d\n\n", i);
        kill(getppid(), SIGUSR1);
        exit(1);
      }
    }
    else{
      if(i == 0)
        pid_fils1 = pid_fork1; /* Si c'est le premier fils on sauvegarde son pid pour que son frere puisse l'afficher */
    }
  }

  sigdelset(&mask, SIGUSR1);
  sigsuspend(&mask);
  sigsuspend(&mask);
  printf("Infos du pere\n");
  printf("pid : %d\n", getpid());
  printf("ppid : %d\n", getppid());
  printf("Fin du pere %d\n\n", i);
  exit(1);

  return 0;
}
