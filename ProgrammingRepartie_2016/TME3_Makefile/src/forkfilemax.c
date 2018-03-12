#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

void sigusr1_handler(){
  printf("Reveil du pere\n");
  return;
}


int main (void) {
    int fd1, fd2, fd3;
    sigset_t mask;
    struct sigaction act_usr1;

    act_usr1.sa_flags = 0;
    act_usr1.sa_handler = sigusr1_handler;
    sigaction(SIGUSR1, &act_usr1, NULL);

    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    if ((fd1 = open ("./fich1", O_RDWR| O_CREAT | O_TRUNC, 0600)) == -1) {
      perror("./fich1");
      return errno;
    }
    if (write (fd1,"abcde", strlen ("abcde")) == -1) {
      perror("./fich1");
      return errno;
    }


    if (fork () == 0) {

        if ((fd2 = open ("./fich1", O_RDWR)) == -1) {
      	  perror("./fich1");
      	  return errno;
      	}
        printf("Ecriture 123\n");
        if (write (fd1,"123", strlen ("123")) == -1) {
      	  perror("./fich1");
      	  return errno;
      	}
        kill(getppid(), SIGUSR1);
        printf("Ecriture 45\n");
        if (write (fd2,"45", strlen ("45")) == -1) {
      	  perror("./fich1");
      	  return errno;
      	}
        close(fd2);
    } else {
        sigdelset(&mask, SIGUSR1);
        sigsuspend(&mask);
        fd3 = dup(fd1);
        if (lseek (fd3,0,SEEK_SET) == -1) {
      	  perror("./fich1");
      	  return errno;
      	}
        printf("Ecriture fg\n");
        if (write (fd3,"fg", strlen ("fg")) == -1) {
      	  perror("./fich1");
      	  return errno;
      	}

        printf("Ecriture hi\n");
        if (write (fd1,"hi", strlen ("hi")) == -1)  {
      	  perror("./fich1");
      	  return errno;
      	}
        wait (NULL);
        close (fd1);
        close(fd3);
        return EXIT_SUCCESS;
    }

    return 0;
}
