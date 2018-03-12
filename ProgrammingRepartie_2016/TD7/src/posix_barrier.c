#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

/* Solution 1 avec compteur partagé*/



int main(int argc, String argv[]){
	pid_t pid_fork1;
	int i = 0, N, shm_fd;
	sem_t sema_barriere;
	if(argc != 2){
		perror("Le programme prend en argument le nombre de processus à créer\n");
		return EXIT_FAILURE;
	}

	N = argv[1];
	shm_fd = shm_open("shm1", O_RDWR | O_CREAT, 0644);
	ftruncate(shm_fd, sizeof(sem_t));
	 

	for(i=0; i<N; i++){
		if((pid_fork1 = fork()) == -1 ){
			 perror("Erreur de creation de fils");
			 return errno;
		}
		else if(pid_fork1 == 0){
			break;
			
		}
		else{
		 
		}
	}

	return 0;


}
