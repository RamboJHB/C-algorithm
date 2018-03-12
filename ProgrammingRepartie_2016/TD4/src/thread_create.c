#define _XOPEN_SOURCE 700
#define _POSIX_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/*Pour compiler utiliser make LDFLAGS='-lpthread'*/


/*La fonction qu'execute le thread ne peut pas prendre n'importe quel argument 
 elle prend void * args, le type de retour doit etre void*  */
void * routine_thread(void* args){
	/*Correction */
	int* pt2;
	int i = *((int *)args); /* On recupere la valeur associee au pointeur*/
	free(args); /* C'est ici que l'on free les i qu'on a alloue dans le main*/
	printf("Mon numero de creation : %d\n", i);
	printf("Mon identite : %lu\n", pthread_self());

	pt2 = malloc(sizeof(int));
	*pt2 = i*2;
	pthread_exit(pt2);

	/*printf("Mon numero de creation : %d\n", numeroCrea);
	printf("Mon identite : %lu\n", pthread_self());
	*numeroCrea *= 2;
	pthread_exit(*numeroCrea);
	free(numeroCrea);*/
}

int main(int argc, char* argv[]){
	int i = 0, num_erreur = 0, N;
	int* pt;
	char msg_err[40];
	pthread_t* tab_tid;
	int * retval;

	if(argc != 2){
		perror("Veuillez preciser un argument indiquant le nombre de thread a creer");
		return EXIT_FAILURE;
	}

	N = atoi(argv[1]);
	tab_tid = malloc(N * sizeof(pthread_t));

	/* Pas besoin d'ouvrir stderr, il est ouvert de base dans le main
	if( (fd_stderr = open(STDERR_FILENO , O_WRONLY, 0644)) == -1 ){
		perror("Erreur d'ouverture du stderr");
		return errno;
	}
	*/

	for(i = 0; i< N; i++){
		 /* On ne peut pas lui envoyer la valeur directement de i, parce que la valeur de i est dans la pile du main, 
			* donc sa valeur peut changer entre temps, ici on alloue a chaque fois un nouvel espace en memoire pour le i */
		pt = malloc(sizeof(int));
		*pt = i;

		/* Pthreads n'indiquent pas les erreurs dans errno, possible d'utiliser strerror*/
		if( (num_erreur = pthread_create(&tab_tid[i], NULL, routine_thread, pt )) != 0){
			snprintf(msg_err, sizeof(msg_err), "Erreur de creation de thread : %d", num_erreur );			
			if( write(STDERR_FILENO, msg_err, sizeof(msg_err)) == -1){
				perror("Erreur d'ecriture dans stderr\n");
				return errno;
			}
		} 		
	} 	

	for(i= 0; i< N; i++){
		 /*ici la fonction pthread prend en argument un (void**), donc on caste une adresse de 
		pointeur pour lui donner en arguement*/
		pthread_join(tab_tid[i], (void**) &retval );
		printf("Valeur de retour : %d\n", *retval);
		free(retval); /*pourquoi ?*/
	}

	free(tab_tid);
	
	return 0;
}
