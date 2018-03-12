#define _POSIX_SOURCE 1
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "producteur_consommateur.h"

/*Inclure unistd.h pour STDIN_FILENO*/
/*Pas besoin de beaucoup de tests car ce n'est pas quelque chose de circulaire + le cond_wait protege de pas mal de situation*/

int stack_size; /* Indique le sommet de la pile, elle vaut -1 s'il n'y a aucun element dans le tableau*/
int flag;
char tab[100]; /* La pile sur laquelle viendront le producteur et le consommateur */
pthread_mutex_t mutex_pile;
pthread_cond_t empty_cond, full_cond;

void push(char c){
	pthread_mutex_lock(&mutex_pile);
	printf("push en cours\nstack_size: %d\n\n", stack_size);
	while(stack_size == 99){
		pthread_cond_wait(&full_cond, &mutex_pile);
	}
	stack_size++; /*On doit incrementer avant de stocker car stack_size initialise a -1 ET aussi parce que le stack_size pointe vers la derniere case ou il y a un caractere et non pas la premiere case vide*/
	tab[stack_size] = c;
	if(stack_size==0){
			flag = 1;
			pthread_cond_broadcast(&empty_cond);
	}
	pthread_mutex_unlock(&mutex_pile);
}

char pop(){
	char cpy;
	pthread_mutex_lock(&mutex_pile);
	printf("pop en cours\nstack_size: %d\n", stack_size);
	while(stack_size == -1){
		pthread_cond_wait(&empty_cond, &mutex_pile);
	}
	printf("Avant lecture du pop\n");
	cpy = tab[stack_size];
	printf("Apres lecture du pop\n\n");
	stack_size--; /*On doit decrementer apres avoir lu*/
	if(stack_size==98)
			pthread_cond_broadcast(&full_cond); /*Je pense que cond_wait les reveillera uniqument au moment ou il aura le verrou mutex_pile*/
	pthread_mutex_unlock(&mutex_pile);
	return cpy;
}

void* routine_producteur(){
	PRODUCTEUR; /*lit sur l'entree standard puis push */
	pthread_exit(0);
}

void* routine_consommateur(void* arg){
	CONSOMMATEUR;
	pthread_exit(0);
}


int main(int argc, char * argv[]){
	pthread_t tid_tab[2];
	int i;
	int* retval;

	stack_size = -1;
	flag = 0;
	if(pthread_create(&tid_tab[0], NULL, routine_producteur, NULL) != 0){
		perror("Erreur de creation du thread");
		return errno;
	}
	if(pthread_create(&tid_tab[1], NULL, routine_consommateur, NULL) != 0){
		perror("Erreur de creation du thread");
		return errno;
	}

	for(i = 0 ; i < 2; i++){
		if(pthread_join(tid_tab[i], (void**) &retval ) != 0 || *retval != 0){
			perror("Erreur join");
			return errno;
		}
	}

	return 0;
}
