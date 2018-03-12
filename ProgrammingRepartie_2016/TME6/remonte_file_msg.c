#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mqueue.h>

/*Ingrédient file de message */

/*Exercice 3 TME6*/

int main(int argc, char* argv[]){
	int i = 0, N, sum = 0;
	pid_t pid_fork1;

	struct mq_attr attr;
	char c, *buf;
	mqd_t mq_des;
	unsigned int prio;

	if(argc != 2){
		perror("Le programme prend en argument le nombre de thread à créer\n");
		return EXIT_FAILURE;
	}

	N = atoi(argv[1]);

	/*A la création de la file de message il est important de préciser la taille de ce qu'on envoie en attribut*/
	if((mq_des = mq_open("/file2", O_RDWR | O_CREAT, 0644, NULL)) == -1){
		perror("Erreur de création du file");
		return EXIT_FAILURE;
	}

	if(mq_getattr(mq_des, &attr) == -1){
		perror("Erreur de recuperation des attributs du mq");
		return errno;
	}
	buf = malloc(attr.mq_msgsize);

	for(i=0; i<N; i++){
		if((pid_fork1 = fork()) == -1 ){
			perror("Erreur de creation de fils");
			return errno;
		}
		else if(pid_fork1 == 0){
			srand(time(NULL) ^ (getpid()<<16)); /* sinon le seed est le même pour tout le monde*/
			c = (int) (10*(float)rand()/RAND_MAX + '0'); /*Conversion du int en char*/
			if(mq_send(mq_des, &c, sizeof(char), 0) == -1){
				perror("Erreur d'envoi du message\n");
				return errno;
			}
			printf("La fils %d a généré : %c\n", i, c);
			close(mq_des);
			exit(1);
		}
		else{
			continue;
		}
	}

	for(i = 0; i<N; i++){
		wait(NULL);
	}
	for(i = 0; i<N; i++){
		if(mq_receive(mq_des, buf, attr.mq_msgsize, &prio) == -1){
			perror("Erreur de réception du message");
			return errno;
		}
		printf("Numéro aléatoire reçu : %s\n", buf);
		sum += atoi(buf);
	}
	printf("La somme des valeurs aléatoires est : %d\n", sum);

	mq_unlink("/file2");

	return 0;
}
