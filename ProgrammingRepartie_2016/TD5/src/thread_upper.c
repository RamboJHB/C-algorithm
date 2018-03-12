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

void * t_routine(void* path){
	int* pt = malloc(sizeof(int));
	if(upper(path) != EXIT_SUCCESS){
		*pt = 1;
		printf("La conversion du fichier %s a échouée\n", (char*)path); 
		pthread_exit(pt);
	}	
	*pt = 0;
	pthread_exit(pt);
}

int main(int argc, char* argv[]){
	int i = 0, cpt_defaillant = 0;
	int *retval;
	pthread_t* tab_tid;	

	if(argc == 1){
		perror("Vous devez préciser au moins un fichier en argument\n");
		return EXIT_FAILURE;
	}

	tab_tid = malloc(argc * sizeof(pthread_t));

	for(i = 1; i<argc; i++){
		if(pthread_create(&tab_tid[i], NULL, t_routine, argv[i]) != 0){
			perror("Erreur de création de thread\n");
			return errno;	
		}
	}

	for(i = 1; i<argc; i++){
		pthread_join(tab_tid[i], (void**) &retval);
		if(*retval !=  0){
			cpt_defaillant++;
		}
	}

	printf("Il y a eu %d threads défaillants\n", cpt_defaillant);

	free(tab_tid);
	return cpt_defaillant;
}


