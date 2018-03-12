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


int somme, N, cpt, flag;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/*On utilise ici un flag car si on a loupe le signal, on ne veut pas wait, sinon on resterait bloque*/

/*Si on utilise une declaration statique pour le mutex il faut l'initialiser directement sinon erreur de compilation, sinon utiliser la declaration dynamique avec init*/

void * routineFirstT(){
	pthread_mutex_lock(&m);
	while(!flag){
		printf("Condition du wait\n");
		pthread_cond_wait(&cond , &m);
	}	
	pthread_mutex_unlock(&m);

	printf("La somme des nombres aleatoire est : %d\n", somme);	
	pthread_exit(NULL);
}

/*La fonction qu'execute le thread ne peut pas prendre n'importe quel argument 
 elle prend void * args, le type de retour doit etre void*  */
void * routine_thread(){
	
	int alea = (int) (10*((double)rand())/ RAND_MAX);
	printf("Le nombre genere : %d\n", alea);
	printf("Mon identite : %lu\n", pthread_self());
	printf("La valeur de N est : %d\n", N);	
	
	pthread_mutex_lock(&m);
	somme += alea;
	flag = 1;
	if(++cpt == (N-1)){
		printf("Le signal est envoye\n");
		pthread_cond_signal(&cond);	
	}
	pthread_mutex_unlock(&m);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]){
	int i = 0, num_erreur = 0;
	char msg_err[40];
	pthread_t* tab_tid;
	srand(time(NULL)); /* on seed le random */	
	
	somme = 0;
	cpt = 0;
	flag = 0;

	if(argc != 2){
		perror("Veuillez preciser un argument indiquant le nombre de thread a creer\n");
		return EXIT_FAILURE;
	}

	N = atoi(argv[1]);
	tab_tid = malloc(N * sizeof(pthread_t));

	for(i = 0; i< N; i++){
		if(i == 0){	
			if( (num_erreur = pthread_create(&tab_tid[i], NULL, routineFirstT , NULL )) != 0){
				snprintf(msg_err, sizeof(msg_err), "Erreur de creation de thread : %d", num_erreur );
				if( write(STDERR_FILENO, msg_err, sizeof(msg_err)) == -1){
					perror("Erreur d'ecriture dans stderr\n");
					return errno;
				}
			}
		}

		else if( (num_erreur = pthread_create(&tab_tid[i], NULL, routine_thread, NULL )) != 0){
			snprintf(msg_err, sizeof(msg_err), "Erreur de creation de thread : %d", num_erreur );			
			if( write(STDERR_FILENO, msg_err, sizeof(msg_err)) == -1){
				perror("Erreur d'ecriture dans stderr\n");
				return errno;
			}
		} 		
	} 	

	for(i= 0; i< N; i++){
		pthread_join(tab_tid[i], NULL );
	}
	
	free(tab_tid);
	
	return 0;
}
