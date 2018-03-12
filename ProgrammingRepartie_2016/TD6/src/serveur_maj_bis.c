#define _XOPEN_SOURCE 700
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


/*Penser à créer le pipe avant le fork*/
/*Le & n'est pas dans argv*/

int fd_pipe;
char* tube;

void sigint_handler(){
	printf("Fermeture du pipe\nFin du serveur\n");
	/*close(fd_pipe);*/
	unlink(tube);
	exit(1);
}

int main(int argc, char* argv[]){
	int i = 0, nb_char;
	char buf[100];
	sigset_t mask;
	struct sigaction act_int;

	if(argc != 2){
		perror("Le premier argument doit être le nom du pipe");
		return EXIT_FAILURE;
	}

	act_int.sa_flags = 0;
	act_int.sa_handler = sigint_handler;
	sigaction(SIGINT, &act_int, NULL);

	sigfillset(&mask);
	sigdelset(&mask, SIGINT);
	sigprocmask(SIG_SETMASK, &mask, NULL);

	tube = argv[1];

	if((fd_pipe = mkfifo(tube, 0760)) == -1){
		if(errno == EEXIST){
			/*cas où le pipe existe déjà, on ouvre le pipe*/
			if((fd_pipe = open(tube, O_RDONLY, 0644)) == -1){
				perror("Erreur d'ouverture du pipe");
				return errno;
			}
		}
		else{
			perror("Erreur de création du pipe");
			return errno;
		}
	}

	while(1){
		i = 0;
		/* SI LE NOMBRE D'ECRIVAIN EST NUL ALORS LE READ RENVOIE 0 ET N'EST PAS BLOQUANT*/
		if( (nb_char = read(fd_pipe, buf, sizeof(buf))) == -1){
			perror("Erreur de lecture sortie standard serveur\n");
			printf("errno : %d", errno);
			return errno;
		}
		while(i < nb_char){
			buf[i] = toupper(buf[i]);
			i++;
		}
		if(write(STDOUT_FILENO, buf, nb_char) == -1){
			perror("Erreur d'écriture sortie standard serveur");
			return errno;
		}
	}

	return 0;

}
