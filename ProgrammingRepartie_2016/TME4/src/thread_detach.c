#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

/*Pour compiler utiliser make LDFLAGS='-lpthread'*/

int somme, cpt, N;
pthread_mutex_t mutex_somme = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_cpt = PTHREAD_COND_INITIALIZER;

/*On caste en pointeur du type que l'on veut puis on en prend la valeur*/
void* thread_routine(void* ident){
	int random = (int) (10*((double)rand())/ RAND_MAX);
	int *rand_ptr = malloc(sizeof(int));
	printf("Mon numÃ©ro de crÃ©ation est le : %d\n", *((int*)(ident)) );
	printf("Le numÃ©ro gÃ©nÃ©rÃ© par le thread %d est %d\n", *((int*)(ident)) , random);

	pthread_mutex_lock(&mutex_somme);
	somme+=random;
	cpt+= 1;
	if(cpt == N)
		pthread_cond_signal(&cond_cpt);
	pthread_mutex_unlock(&mutex_somme);

	*rand_ptr = random;
	free(ident); /* On free les malloc de tmp*/
	pthread_exit(NULL);
}

void* thread_ini_routine(){
	pthread_mutex_lock(&mutex_somme);
	pthread_cond_wait(&cond_cpt, &mutex_somme);
	printf("La somme des valeurs alÃ©atoire est de : %d\n", somme);
	pthread_mutex_unlock(&mutex_somme);
	pthread_exit(NULL);

}


int main(int argc, char* argv[]){
	int i = 0;
	int *tmp;
	pthread_t* tid_tab; /*UtilisÃ©e pour sauvegarder les id des threads*/

	/*Test du nombre d'argument du programme*/
	if(argc != 2){
		perror("Le programme prend en argument le nombre de thread a creer\n");
		return EXIT_FAILURE;
	}

	N = atoi(argv[1]);
	cpt = 0;
	tid_tab = malloc((N+1) * sizeof(pthread_t));
	srand(time(NULL));
	somme = 0;

	if(pthread_create(&tid_tab[0], NULL, thread_ini_routine, NULL) != 0){
			perror("Erreur de creation du thread\n");
			return EXIT_FAILURE;
	}

	/*Boucle de crÃ©ation des threads, on passe en argument son numÃ©ro de crÃ©ation*/
	for(i = 1; i<N+1; i++){
		tmp = malloc(sizeof(int));
		*tmp = i;
		if(pthread_create(&tid_tab[i], NULL, thread_routine, tmp) != 0){
			perror("Erreur de creation du thread\n");
			return EXIT_FAILURE;
		}
		if(pthread_detach(tid_tab[i]) != 0){
			perror("Erreur de dÃ©tachement du thread\n");
			return EXIT_FAILURE;
		}
	}

	if(pthread_join(tid_tab[0], NULL) != 0){
			perror("Erreur de join\n");
			return EXIT_FAILURE;
	}

	printf("Fin du programme\n");
	free(tid_tab);

	return 0;
}
