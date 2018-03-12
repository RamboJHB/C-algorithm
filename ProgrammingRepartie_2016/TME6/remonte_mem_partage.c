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

/*Ingrédient mémoire partagée */

/*Exercice 1 TME6*/

int main(int argc, char* argv[]){
	pid_t pid_fork1;
	int i = 0, N, shm_fd, sum = 0;
	int *rand_tab;


	if(argc != 2){
		perror("Le programme prend en argument le nombre de thread à créer\n");
		return EXIT_FAILURE;
	}

	N = atoi(argv[1]);

	if((shm_fd = shm_open("monshm", O_RDWR | O_CREAT, 0644)) == -1){
		perror("Erreur de création du shm");
		return EXIT_FAILURE;
	}

	if(ftruncate(shm_fd, N*sizeof(int)) == -1){
		perror("Erreur d'allocation de taille pour la shm");
		return EXIT_FAILURE;
	}

	if((rand_tab = mmap(NULL, N*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)) == MAP_FAILED){
		perror("Erreur de mapping du segment partagé");
		return errno;
	}

	for(i=0; i<N; i++){
		if((pid_fork1 = fork()) == -1 ){
			 perror("Erreur de creation de fils");
			 return errno;
		}
		else if(pid_fork1 == 0){	
			srand(time(NULL) ^ (getpid()<<16)); /* sinon le seed est le même pour tout le monde*/
			rand_tab[i] = (int) (10*(float)rand()/RAND_MAX);
			printf("La fils %d a généré : %d\n", i, rand_tab[i]);
			close(shm_fd);	
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
		printf("Rand_tab %d : %d\n", i, rand_tab[i]);
		sum += rand_tab[i];
	}
	printf("La somme des valeurs aléatoires est : %d\n", sum);

	shm_unlink("monshm");
	
	return 0;
}

