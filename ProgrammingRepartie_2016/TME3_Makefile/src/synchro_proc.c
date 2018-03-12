#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void sigusr_handler(int signum){
  switch(signum){
    case SIGUSR1:
      printf("Processus P3 cree\n");
      break;
    case SIGUSR2:
      printf("Processus P3 termine\n");
      break;
  }
  return;
}

/*ATTENTION BIEN PENSER A NE DEMASQUER QUE SIGUSR1 PUIS ENSUITE SIGUSR2 SINON LES DEUX SIGNAUX SONT TRAITES EN MEME TEMPS DANS LE PREMIER SIGSUSPEND ET LE MEC RESTE BLOQUE DANS LE SECOND*/

int main(int argc, char* argv[]){
  int pid_gdpere, status;
  pid_t pid_fork;
  struct sigaction act_usr1;
  sigset_t mask_full, mask;

  act_usr1.sa_flags = 0;
  act_usr1.sa_handler = sigusr_handler;
  sigaction(SIGUSR1, &act_usr1, NULL);
  sigaction(SIGUSR2, &act_usr1, NULL);


  sigfillset(&mask_full);
  sigprocmask(SIG_SETMASK, &mask_full, NULL);


  if((pid_fork = fork()) == -1){
    perror("Erreur de creation du fils\n");
    return errno;
  }
  else if(pid_fork == 0){
    pid_gdpere = getppid();
    if((pid_fork = fork()) == -1){
      perror("Erreur de creation du petit fils\n");
      return errno;
    }
    else if(pid_fork == 0){
      if(kill(pid_gdpere, SIGUSR1) == -1){
        perror("Erreur kill par petit fils SIGUSR1\n");
      }
      exit(1);
    }
    else{
      wait(&status);
      if(WIFEXITED(status)){
        if(kill(pid_gdpere, SIGUSR2) == -1){
            perror("Erreur kill par fils SIGUSR2\n");
        }
      }
      exit(1);
    }
  }
  else{
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigsuspend(&mask);
    sigdelset(&mask, SIGUSR2);
    sigsuspend(&mask);
    printf("fin sigsuspend2\n");
    wait(NULL);
    printf("Processus P2 termine\n");
  }


  return 0;
}
