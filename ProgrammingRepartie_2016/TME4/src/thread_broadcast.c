#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex_cpt = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_cpt = PTHREAD_COND_INITIALIZER;
int cpt;

void wait_barrier(int N){
	pthread_mutex_lock(&mutex_cpt);
	if(cpt == N-1){
		printf("CAS BROADCAST\n");
		pthread_cond_broadcast(&cond_cpt);
	}
	else{
		cpt++;
		printf("CPT : %d\n", cpt);
		pthread_cond_wait(&cond_cpt, &mutex_cpt);
	}
	pthread_mutex_unlock(&mutex_cpt);
	return;

}

void* thread_func (void *arg) {
   printf ("avant barriere\n");
   wait_barrier ( *((int *)arg) );
   printf ("après barriere\n");
   pthread_exit ( NULL);
}

int main(int argc, char* argv[]){
	int i = 0, N;
	int* N_ptr;
	pthread_t *tid_tab;

	if(argc != 2){
		perror("L'argument du programme indique le nombre de thread à créer\n");
		return EXIT_FAILURE;
	}

	N_ptr = malloc(sizeof(int));
	N = atoi(argv[1]);
	*N_ptr = N;
	printf("N : %d\n", N);
	tid_tab = malloc(N * sizeof(pthread_t));
	cpt = 0;

	for(i = 0; i< N; i++){
		if(pthread_create(&tid_tab[i], NULL, thread_func, N_ptr) != 0){
			perror("Erreur de création du thread\n");
			return EXIT_FAILURE;
		}
	}

	for(i = 0; i< N; i++){
		if(pthread_join(tid_tab[i], NULL) != 0){
			perror("Erreur de création du thread\n");
			return EXIT_FAILURE;
		}
	}

	return 0;
}
