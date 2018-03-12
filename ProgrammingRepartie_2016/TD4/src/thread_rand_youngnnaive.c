#define _XOPEN_SOURCE 700
#define _POSIX_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

/*Pour compiler utiliser make LDFLAGS='-lpthread'*/

int somme;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; 
/*Si on utilise une declaration statique pour le mutex il faut l'initialiser directement sinon erreur de compilation, sinon utiliser la declaration dynamique avec init*/

/*La fonction qu'execute le thread ne peut pas prendre n'importe quel argument 
 elle prend void * args, le type de retour doit etre void*  */
void * routine_thread(){
	/* pthread_mutex_t m = *((pthread_mutex_t *)args); On recupere la valeur associee au pointeur*/
	
	int alea = (int) (10*((double)rand())/ RAND_MAX);
	printf("Le nombre genere : %d\n", alea);
	printf("Mon identite : %lu\n", pthread_self());
	
	/*pthread_mutex_lock((pthread_mutex_t *) args);
	somme += alea;
	pthread_mutex_unlock((pthread_mutex_t *) args);*/
	
	pthread_mutex_lock(&m);
	somme += alea;
	pthread_mutex_unlock(&m);

	pthread_exit(NULL);

}

int main(int argc, char* argv[]){
	int i = 0, num_erreur = 0, N;
	char msg_err[40];
	pthread_t* tab_tid;
	/*pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; Il aurait aussi ete possible de passer le mutex
	* en argument du pthread_create, NE MARCHE PAS SI ON PASSE LE MUTEX EN ARGUMENT DU THREAD
	*/ 
	srand(time(NULL)); /* on seed le random */	
	
	somme = 0;

	if(argc != 2){
		perror("Veuillez preciser un argument indiquant le nombre de thread a creer");
		return EXIT_FAILURE;
	}

	N = atoi(argv[1]);
	tab_tid = malloc(N * sizeof(pthread_t));

	for(i = 0; i< N; i++){

		/* Pthreads n'indiquent pas les erreurs dans errno, possible d'utiliser strerror*/
		/* if( (num_erreur = pthread_create(&tab_tid[i], NULL, routine_thread, &m )) != 0) */

		if( (num_erreur = pthread_create(&tab_tid[i], NULL, routine_thread, NULL )) != 0){
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
		pthread_join(tab_tid[i], NULL );
	}
	
	printf("La somme des nombres aleatoire est : %d\n", somme);

	free(tab_tid);
	
	return 0;
}
