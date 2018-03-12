#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
	int pid = 0, i = 0, frere = 0;
	for(i=0; i<2; i++){
		if( (pid = fork()) == -1){
			printf("erreur création fork");
		}
		else if(pid == 0){
			if(i==0){
				printf("PID  du Fils 1 :  %d\n", getpid());
				printf("père du fils 1 : %d\n", getppid());
			}
			if(i==1){
				printf("PID du Fils 2 : %d\n", getpid());
				printf("père du fils 2: %d\n", getppid());
				printf("PID du frère  : %d\n", frere);
			}

			if( (pid=fork()) == -1){
				printf("erreur création fork");
			}
			else if(pid == 0){
				if(i==0){
					printf("PID  du Fils 1.1 : %d\n", getpid());
					printf("père du Fils 1.1 : %d\n", getppid());
				}
				else{
					printf("PID du Fils  2.1 : %d\n", getpid());
					printf("père du Fils 2.1 : %d\n", getppid());
				}
				exit(1);
			}
			else{
				wait(NULL);
				exit(1);
			}

		}
		else{
			if(i==0)
				frere = pid;
		}
	}
	i=0;
	for(i = 0; i<2; i++){
		wait(NULL);
	}
	printf("fin du processus originel pid = %d\n", getpid());
	return 0;
}
