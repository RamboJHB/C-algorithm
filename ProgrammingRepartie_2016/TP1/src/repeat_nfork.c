#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int nfork(int nb_fils);


int main (void) {
	int p;
	int i=1; int N = 3;
	do {
		p = nfork (i) ;
		if (p != 0 )
			 printf ("%d \n",p); 
	 } while ((p ==0) && (++i<=N));
		printf ("FIN\n");
	return EXIT_SUCCESS;
}

int nfork(int nb_fils){
	pid_t fpid;
	int count=0;
	fpid=f 	


}
