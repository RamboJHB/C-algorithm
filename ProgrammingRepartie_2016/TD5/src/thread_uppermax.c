#define _XOPEN_SOURCE 700
#define _POSIX_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "lib_upper.h"

/* Prend noms de fichiers en argument; doit créer autant de threads que de fichiers et les lancer en 
  parallèle. EXIT_SUCCESS vaut 0 */

int cpt;
int nb_fichier;
pthread_mutex_t mutex_cpt = PTHREAD_MUTEX_INITIALIZER;

/* ATTENTION QUAND ON PASSE ARGV QUI EST CHAR** PASSER &argv[0] */

void * t_routine(void* argv){
	int* pt = malloc(sizeof(int));
	int cptlocal;
	char** str = (char**)argv;
	pthread_mutex_lock(&mutex_cpt);
	while(cpt<(nb_fichier+2)){
		cptlocal = cpt;
		cpt++;
		printf("Nom fichier : %s\n", str[cptlocal]);
		pthread_mutex_unlock(&mutex_cpt);
		if(upper(str[cptlocal]) != EXIT_SUCCESS){
			*pt = cptlocal;
			printf("La conversion du fichier %s a échouée\n", str[cptlocal]); 
			pthread_exit(pt);
		}
		pthread_mutex_lock(&mutex_cpt);
	}

	pthread_mutex_unlock(&mutex_cpt);
	*pt = 0;
	printf("Terminaison de thread\n");
	pthread_exit(pt);
}

int main(int argc, char* argv[]){
	int i = 0, cpt_defaillant = 0, nb_threads = 0;
	int *retval;
	pthread_t* tab_tid;	

	if(argc < 4){
		perror("Vous devez préciser nb threads et une liste de fichiers supérieur au nb thread\n");
		return EXIT_FAILURE;
	}
	
	nb_threads = atoi(argv[1]);
	nb_fichier = argc - 2;
	cpt = 2;  
	tab_tid = malloc(argc * sizeof(pthread_t));

	for(i = 0; i<nb_threads; i++){
		pthread_mutex_lock(&mutex_cpt);
		if(cpt<nb_fichier &&  pthread_create(&tab_tid[i], NULL, t_routine, &argv[0]) != 0){
			perror("Erreur de création de thread\n");
			return errno;	
		}
		pthread_mutex_unlock(&mutex_cpt);
	}

	for(i = 0; i<nb_threads; i++){
		pthread_join(tab_tid[i], (void**) &retval);
		if(*retval !=  0){
			cpt_defaillant++;
		}
	}

	printf("Il y a eu %d traitements défaillants\n", cpt_defaillant);

	free(tab_tid);
	return cpt_defaillant;
}


