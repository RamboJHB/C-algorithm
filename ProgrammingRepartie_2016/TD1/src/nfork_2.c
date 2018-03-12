#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

int nfork(int n){
	int i = 0, cpt = 0;
    pid_t pid;
	for(i=0; i<n; i++){
		if( (pid = fork()) == -1){
			perror("erreur création fork");			
			break;
		}
		else if(pid == 0){
            printf("child %d from%d\n",getpid(),getppid());
			exit(1);
		}
		else{
			cpt++;
            printf ("pid %d %d \n",getpid(),cpt); 
		}
	}
	
	if(cpt == 0)
		return -1;
	else 
		return cpt; 
}


int main (void) {
    int p;
    int i=3; 
    int N = 7;
    do {
        p = nfork (i) ;
        if (p != 0 )
              printf ("nfork returns p=%d \n",p); 
        } while ((p ==0) && (++i<=N));
    sleep(3);
    printf ("pid %d FIN\n",getpid());
    return EXIT_SUCCESS;
}
