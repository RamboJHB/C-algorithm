#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Chaque processus a sa propre table de descripteur, la table des fichiers ouverts est commune a tout les processus, donc deux descripteurs de
   deux processus differents peuvent pointer sur la meme entree de la table des fichiers ouverts, l'offset est donc partage entre les deux processus.
   ATTENTION dup(oldfd) copie oldfd dans le plus petit numero de descripteur non utilise, dans notre cas c'est 4, etant donne que 3 est deja occupe par
   oldfd et que les trois premiers sont occupes par respectivement stdin, stdout, stderr. Apres la copie il retourne 4 et la valeur de fd reste a 3
   ATTENTION offset != descripteur*/

int main (void) {
    int fd1, fd2, fd3;
    if ((fd1 = open ("./fich1", O_RDWR| O_CREAT | O_TRUNC, 0600)) == -1) {
      perror("./fich1");
      return errno;
    }
    printf("Ecriture abcde\n");
    if (write (fd1,"abcde", strlen ("abcde")) == -1) {
      perror("./fich1");
      return errno;
    }
    printf("taille char : %lu\n", sizeof("abcde") );
    printf("fd1 apres ecriture abcde : %d\n", fd1 );
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
        printf("Ecriture 45\n");
        if (write (fd2,"45", strlen ("45")) == -1) {
      	  perror("./fich1");
      	  return errno;
      	}
        close(fd2);
    } else {
        printf("fd1 debut pere : %d\n", fd1);
        fd3 = dup(fd1);
        if (lseek (fd3,0,SEEK_SET) == -1) {
      	  perror("./fich1");
      	  return errno;
      	}
        printf("fd3 : %d\n", fd3 );
        printf("fd1 : %d\n", fd1 );
        printf("Ecriture fg\n");
        if (write (fd3,"fg", strlen ("fg")) == -1) {
      	  perror("./fich1");
      	  return errno;
      	}
        printf("Ecriture hi, fd1 : %d\n", fd1);

        if (write (fd1,"hi", strlen ("hi")) == -1)  {
      	  perror("./fich1");
      	  return errno;
      	}
        wait (NULL);
        close (fd1);
        close(fd3);
        return EXIT_SUCCESS;
    }
}
