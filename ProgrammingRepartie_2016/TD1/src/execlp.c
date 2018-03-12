#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>


int main(int argc, char **argv) {
    pid_t pid;
    int  j=0; 
    int i = 0;
    printf("main pid %d\n",getpid());
    while (i < 2) {
       i ++;
       if ((pid = fork ()) == -1) {
            perror ("fork");
           return errno;
        }
     else if (pid == 0) j=i;
     
    }
    if (j == 2) {
      sleep (2);
        //if (execl("~/documents/linux_c/ProgrammingRepartie/TD1/src/sleep","sleep","2",NULL)<0) perror("execl");
//        if (execlp("sleep","sleep","2",NULL)<0) perror("execlp");
        printf ("pid %d sans fils \n",getpid());
    }
    else {
       printf ("pid %d  %d fils \n ",getpid(), (i-j) );
       while (j < i) {
            j++;
            wait (NULL);
       }
     }
     return EXIT_SUCCESS;
} 
