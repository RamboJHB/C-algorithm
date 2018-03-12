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
 * de son fils. Utilisation de kill, sigaction, sigsuspend, sigprocmask, lorsque le dernier
 * fils a affiche tous les pid, il envoie un SIGUSR1 ou 2 a son pere, etc. sigaction pour
 * redefinir le comportement de SIGUSR1.
 */

pid_t pid_fork; /*Declare comme variable globale pour pouvoir y acceder dans le handler*/
pid_t proc_initial; /*Pour eviter que le premier processus envoie un SIGUSR1 a son pere*/

void sigusr_handler(int sig){
	printf("pid du père : %d\n", getppid());
	printf("pid de lui même : %d\n", getpid());
	printf("pid du fils : %d\n", pid_fork);
    sleep(1);
	if(getpid() != proc_initial){
		kill(getppid(), SIGUSR1);
	}
}


int main(int argc, char* argv[]){
	pid_t* pid_proc;
	sigset_t sigmask;
	sigset_t sigmasksuspend;
	int N, i, j = 0;
	struct sigaction act;

	if(argc != 2){
		perror("N  le nombre de processus à créer");
		return EXIT_FAILURE;
	}

	proc_initial = getpid();

	N = atoi(argv[1]);
	pid_proc = malloc(N*sizeof(pid_t));
	pid_proc[0] = getpid();

	sigfillset(&sigmask);
	sigfillset(&sigmasksuspend);
	sigdelset(&sigmasksuspend, SIGUSR1);

	act.sa_flags = 0;
	act.sa_handler = sigusr_handler;
	sigaction(SIGUSR1, &act, NULL);


	/*
	* On masque tous les signaux, dans le cas ou le signal envoye par
	* le fils est traite avant le sigsuspend, le processus sera bloque.
	* On utilise sigprocmask aussi pour eviter qu'un signal tue le pere,
	* avant que le fils ne soit termine.
	* Les signaux recus lors du sigprocmask seront pendants.
	* Avec sigsuspend on demasquera SIGUSR1 pour le traiter.
	*
	*/
	sigprocmask(SIG_SETMASK, &sigmask, NULL);

	for(i = 1; i<N; i++){
		/*fils*/
		if((pid_fork = fork()) == 0){
			pid_proc[i] = getpid();
			if(i == (N-1)){
				for(j=0; j<N; j++){
					printf("Le pid du processus %d : %d\n" , j, pid_proc[j]);
				}
				kill(getppid(), SIGUSR1);
				printf("Fin du dernier processus\n");
				exit(1);
			}
		}
		/*pere*/
		else{
			sigsuspend(&sigmasksuspend);
			printf("Fin du processus %d\n", i-1);
			exit(1);
		}
	}
	return 0;
}
