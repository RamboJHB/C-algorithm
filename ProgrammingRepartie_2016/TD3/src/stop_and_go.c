#define _XOPEN_SOURCE 700
#define _POSIX_SOURCE 1
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

/* 
 * Chaine de processus; chaque processus en créé un second et ainsi de suite jusqu'à la 
 * création de N processus (processus initial inclus). Le dernier processus affiche les pid 
 * de tous les autres processus, chaque processus affiche son pid celui de son père et celui 
 * de son fils. 
 * Le dernier fils se stop en s'envoyant un signal a lui meme, son pere recevra alors un 
 * SIGCHLD qu'il interceptera avec sigsuspend, a son tour il se stop etc.
 * Le premier processus devra redemarrer son fils avec SIGCONT puis attendra avec sigsuspend
 * un SIGUSR1, le fils enverra a son tour SIGCONT a son fils puis s'arretera etc, le dernier
 * fils enverra SIGUSR1 au processus initial qui affichera "Fin du programme"
 *
 */

pid_t pid_fork; /*Declare comme variable globale pour pouvoir y acceder dans le handler*/
pid_t proc_initial; /*Pour eviter que le premier processus envoie un SIGUSR1 a son pere*/

void sigusr_handler(){
	printf("Fin du programme\n");
	exit(1);
}

void sigchld_handler(){
	sigset_t mask;
	if(getpid() != proc_initial){
		printf("Processus stoppe\n");
		kill(getpid(), SIGSTOP);
		return;
	}
	else{
		/*Le processus initial attend le sigusr du dernier fils*/
		sigfillset(&mask);
		sigdelset(&mask, SIGUSR1);
		printf("Le proc initial attend le dernier fils\n");
		kill(pid_fork, SIGCONT);
		while(1){}
		/*sigsuspend(&mask);*/
		exit(1);
	}
}


int main(int argc, char* argv[]){
	pid_t* pid_proc;
	sigset_t sigmask;
	sigset_t sigmasksuspend;
	int N, i, j = 0;
	struct sigaction act_chld, act_usr1;
	
	if(argc != 2){
		perror("Veuillez préciser en argument une valeur N déterminant le nombre de processus à créer\n");
		return EXIT_FAILURE;
	}

	proc_initial = getpid();

	N = atoi(argv[1]);
	pid_proc = malloc(N*sizeof(pid_t));
	pid_proc[0] = getpid(); 

	sigfillset(&sigmask);
	sigfillset(&sigmasksuspend);
	sigdelset(&sigmasksuspend, SIGCHLD);

	act_chld.sa_flags = 0;
	act_chld.sa_handler = sigchld_handler;
	sigaction(SIGCHLD, &act_chld, NULL);
	act_usr1.sa_flags = 0;
	act_usr1.sa_handler = sigusr_handler;
	sigaction(SIGUSR1, &act_usr1, NULL);	
	
	sigprocmask(SIG_SETMASK, &sigmask, NULL);
			
	for(i = 1; i<N; i++){
		/*fils*/
		if((pid_fork = fork()) == 0){
			pid_proc[i] = getpid();		
			if(i == (N-1)){
				for(j=0; j<N; j++){
					printf("Le pid du processus %d : %d\n" , j, pid_proc[j]);
				}
				printf("Le dernier processus s'est stoppe\n\n");
				kill(getpid(), SIGSTOP);
				 /* A la reprise le dernier fils envoie SIGUSR1 au proc 
				  * initial avant de se terminer*/ 
				kill(SIGUSR1, proc_initial);
				printf("Le dernier processus s'est termine\n\n");
				exit(1);
			}
		}
		/*pere*/
		else{
			printf("Le processus %d s'est stoppe\n", i);
			sigsuspend(&sigmasksuspend);
			printf("Le pid_fork du processus %d est %d", i, pid_fork);
			kill(SIGCONT, pid_fork); 
			printf("Fin du processus %d\n", i-1);
			exit(1);
		}
	}
	return 0;
}
