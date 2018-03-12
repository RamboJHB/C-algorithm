#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int nfork (int nb_fils){
	int cpt=0;
	pid_t pid;
	printf("generate %d fils----------------\n",nb_fils);
	for (int i=0;i<nb_fils;i++){	
		if ((pid=fork())== -1){
			perror ("fork() failed");
			break;		//exit for()
		}
		if (pid==0){			
			printf("ppid:%d pid:%d Im a fils\n",getppid(),getpid());
			return 0;
			printf("fils didnt quit!!!!\n");
		}else{
			cpt++;	//nb_fils++; X also a condition in the for()
		}
	}
	if (nb_fils==0)
		return -1;
	else
		return cpt;
}

int main (void) {
	int p;
	int i=1; int N = 3;
	printf("ppid:%d pid:%d Im your dad\ni=%d,N=%d\n",getppid(),getpid(),i,N);
	do {
		p = nfork (i) ;
		if (p != 0 )
			printf ("%d \n",p); 
	} while ((p ==0) && (++i<=N));
	printf ("FIN\n");
//	sleep(2);
	return EXIT_SUCCESS;
}
