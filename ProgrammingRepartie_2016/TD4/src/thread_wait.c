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

int somme, cpt, N, flag;
pthread_mutex_t mutex_somme = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_cpt = PTHREAD_COND_INITIALIZER;

/*On caste en pointeur du type que l'on veut puis on en prend la valeur*/
void* thread_routine(void* ident){
	int random = (int) (10*((double)rand())/ RAND_MAX);
	int *rand_ptr = malloc(sizeof(int));
	printf("Mon numéro de création est le : %d\n", *((int*)(ident)) );
	printf("Le numéro généré par le thread %d est %d\n", *((int*)(ident)) , random);

	pthread_mutex_lock(&mutex_somme);
	somme+=random;
	cpt+= 1;
	if(cpt == N){
		flag = 1;
		pthread_cond_signal(&cond_cpt);
	}	
	pthread_mutex_unlock(&mutex_somme);
	
	*rand_ptr = random;
	free(ident); /* On free les malloc de tmp*/
	pthread_exit(rand_ptr);
}

void* thread_ini_routine(){
	pthread_mutex_lock(&mutex_somme);
	while(!flag){
		pthread_cond_wait(&cond_cpt, &mutex_somme);
	}
	printf("La somme des valeurs aléatoire est de : %d\n", somme);
	pthread_mutex_unlock(&mutex_somme);
	pthread_exit(NULL);

}


int main(int argc, char* argv[]){
	int i = 0;
	int *tmp, *retval;
	pthread_t* tid_tab; /*Utilisée pour sauvegarder les id des threads*/

	/*Test du nombre d'argument du programme*/
	if(argc != 2){
		perror("Le programme prend en argument le nombre de thread a creer");
		return EXIT_FAILURE;
	}

	N = atoi(argv[1]);	
	tid_tab = malloc((N+1) * sizeof(pthread_t));
	cpt = 0;
	somme = 0;
	flag = 0;
	srand(time(NULL));
	

	if(pthread_create(&tid_tab[0], NULL, thread_ini_routine, NULL) != 0){
			perror("Erreur de creation du thread");
			return EXIT_FAILURE;
	}

	/*Boucle de création des threads, on passe en argument son numéro de création*/
	for(i = 1; i<N+1; i++){
		tmp = malloc(sizeof(int));
		*tmp = i;
		if(pthread_create(&tid_tab[i], NULL, thread_routine, tmp) != 0){
			perror("Erreur de creation du thread");
			return EXIT_FAILURE;
		}
	}


	/*Boucle des join, on récupère une valeur de retour, NE PAS OUBLIER DE CASTER RETVAL EN (VOID**) */
	if(pthread_join(tid_tab[0], NULL) != 0){
			perror("Erreur de join\n");
			return EXIT_FAILURE;
	}
	for(i = 1; i<N+1; i++){
		if(pthread_join(tid_tab[i], (void**)&retval) != 0){
			perror("Erreur de join\n");
			return EXIT_FAILURE;
		} 
		printf("Valeur de retour du thread: %d\n", *retval);
		free(retval); /* On free les malloc de rand_ptr*/
	}

	free(tid_tab);
	
	return 0;
}
