#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

/*Le & n'est pas dans argv*/

int fd_pipe;

int main(int argc, char* argv[]){
	int nb_char;
	char buf[100];

	if(argc != 2){
		perror("Le premier argument doit être le nom du pipe");
		return EXIT_FAILURE;
	}

	if((fd_pipe = open(argv[1], O_WRONLY, 0644)) == -1){
		perror("Erreur d'ouverture du pipe");
		return errno;
	}

	while(1){
		if((nb_char = read(STDIN_FILENO, buf, sizeof(buf))) == -1){
			perror("Erreur de lecture du clavier");
			return errno;
		}
		if(write(fd_pipe, buf, nb_char) == -1){
			perror("Erreur d'écriture dans le pipe par le client");
			return errno;
		}
	}

	close(fd_pipe);
	return 0;

}
