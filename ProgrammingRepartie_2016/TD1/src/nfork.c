#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

int nfork(int n){
	int i = 0, cpt = 0;
    pid_t pid;
	for(i=0; i<n; i++){
		if( (pid = fork()) == -1){
			perror("erreur création fork");			
			break;
		}
		else if(pid == 0){
		 printf("pid:%dIm a fils\n",getpid());
			exit(1);
		}
		else{
			cpt++;
		}
	}
	
	if(cpt == 0)
		return -1;
	else 
		return cpt; 
}


int main(int argc, char* argv[]){
	int choix = 0;
	printf("argv[1]= %s\n", argv[1]);
	if(argc==2 && (choix = atoi(argv[1])) != 0 ){
 		printf("%d forks\n", nfork(choix));
	}	
	return 0;
}
