#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//*Chaine de processus; chaque processus en créé un second et ainsi de suite jusqu'à la création de N processus (processus initial inclus). Le dernier processus affiche les pid de tous les autres processus, chaque processus affiche son pid celui de son père et celui de son fils. Le processus initiale affiche la valeur aléatoire générée par le dernier fils*/


int main(int argc, char* argv[]){
	//faire un tableau de pid_t plutôt
	int pid_fork = 0, i = 1, status = 0 ;

	if(argc != 2){
		perror("Veuillez préciser en argument une valeur N déterminant le nombre de processus à créer");
		return EXIT_FAILURE;
	}
	int N = atoi(argv[1]);
	int pid_proc[N];
	pid_proc[0] = getpid(); 
	for(i = 1; i<N; i++){
	//cas du fils 
		if((pid_fork = fork()) == 0){
			pid_proc[i] = getpid();				
			if(i == (N-1)){
				int j = 0, random_val = 0;
				srand(time(NULL));
				for(j=0; j<N; j++){
					printf("Le pid du processus %d : %d\n" , j, pid_proc[j]);
				}
				random_val = (int) (rand()/(((double) RAND_MAX + 1) / 100));
				printf("Fin du dernier processus\n");
				exit(random_val);
			}
		}
	//cas du père
		else{
			waitpid(pid_fork, &status, 0);
			printf("pid du père : %d\n", getppid());
			printf("pid de lui même : %d\n", getpid());
			printf("pid du fils : %d\n", pid_fork);	
			int retour_fils_rand = 0;
			if(WIFEXITED(status)){
				retour_fils_rand = WEXITSTATUS(status);
			}		
			if(i == 1){
				printf("La valeur aléatoire générée par le dernier fils est : %d\n", retour_fils_rand);
			}
			exit(retour_fils_rand);
	
		}
	}
	return 0;
}					
