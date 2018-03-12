#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <signal.h>
/*Pour compiler utiliser make LDFLAGS='-lpthread'*/

/*Voir TD4/src/thread_create.c si nécessaire */

pthread_mutex_t mutex_flag;
pthread_cond_t cond_principale;
pthread_cond_t reveil;
int flag = 0;

/*On caste en pointeur du type que l'on veut puis on en prend la valeur*/
void* thread_routine(void* ident){
  sigset_t mask;
  sigfillset(&mask);
  sigprocmask(SIG_SETMASK, &mask, NULL);
  /*COND_WAIT*/
  pthread_mutex_lock(&mutex_flag);
  while(flag!=1){
    pthread_cond_wait(&reveil, &mutex_flag);
  }
  pthread_mutex_unlock(&mutex_flag);
  printf("Terminaison de thread\n");
	pthread_exit(NULL);
}

void sig_handler(int sig){
  /*COND_BROADCAST*/
  pthread_mutex_lock(&mutex_flag);
  flag = 1;
  pthread_cond_broadcast(&reveil);
  pthread_mutex_unlock(&mutex_flag);
  return;
}

int main(int argc, char* argv[]){
	int N, i = 0;
	int *tmp;
	pthread_t* tid_tab; /*Utilisée pour sauvegarder les id des threads*/
  sigset_t mask, masksuspend;
  struct sigaction act;

  sigfillset(&mask);
  sigprocmask(SIG_SETMASK, &mask, NULL);

  act.sa_flags = 0;
  act.sa_handler = sig_handler;
  sigaction(SIGINT, &act, NULL);

	/*Test du nombre d'argument du programme*/
	if(argc != 2){
		perror("Le programme prend en argument le nombre de thread a creer\n");
		return EXIT_FAILURE;
	}

	N = atoi(argv[1]);
	tid_tab = malloc(N * sizeof(pthread_t));

	/*Boucle de création des threads, on passe en argument son numéro de création*/
	for(i = 0; i<N; i++){
		tmp = malloc(sizeof(int));
		*tmp = i;
		if(pthread_create(&tid_tab[i], NULL, thread_routine, tmp) != 0){
			perror("Erreur de creation du thread");
			return EXIT_FAILURE;
		}
    printf("Creation du thread %d\n", i);
	}

  printf("Tous mes descendants sont crees.\n");
  printf("Le thread principal se met en attente.\n");
  sigfillset(&masksuspend);
  sigdelset(&masksuspend, SIGINT);
  sigsuspend(&masksuspend);

	/*Boucle des join, on récupère une valeur de retour, NE PAS OUBLIER DE CASTER RETVAL EN (VOID**) */
	for(i = 0; i<N; i++){
		if(pthread_join(tid_tab[i], NULL) != 0){
			perror("Erreur de join\n");
			return EXIT_FAILURE;
		}
	}

  printf("Tous mes descendants se sont termines.\n");

	free(tid_tab);
	return 0;
}
