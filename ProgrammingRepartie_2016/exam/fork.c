#define _XOPEN_SOURCE 700

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (int argc, char* argv[ ]) {
  int level=0; 
  int i,j,N; 
  pid_t pid_fils;
/* if ((argc != 2) || ( (N=atoi(argv[1])) <2 ) || (N >4)){ 
    printf ("le programme recoit comme argument un entier N entre 2 et 4 \n"); 
    exit (1);
  }
*/
  j = N=4;

  for (i=1; i<=N; i++) { 

    if ( j==N ) {   
      for (j=1; j<=N; j++) {
        if ((pid_fils = fork()) ==-1){
           perror("fork");
           exit (1);
        }
        if (pid_fils == 0) {
           level = i;   
           printf ("pid %d level %d: %d \n",getpid(),level,j );
           break;
        }
      } /* for j */
    }  
  } /* for i */

   return 0;
}
