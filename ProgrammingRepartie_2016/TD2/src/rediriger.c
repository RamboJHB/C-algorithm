#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

//stdin est un FILE*
//STDIN_FILENO est un file descriptor le plus souvent 0 
//STDOUT_FILENO est un file descriptor le plus souvent 1
//Dans le main stdin et stdout sont ouverts de base
//on peut sauvegarder les descripteurs en faisant par exemple 
//int stdin, stdout;
//stdin = dup(STDIN_FILENO)
//stdout = dup(STDOUT_FILENO)
//
//Si le stdout s'est ferme on peut le reouvrir en faisant open("/dev/tty", O_WRONLY)
//dup2(source, destination)
//
//Pourquoi ne pas juste restaurer avec un fd egal a 1 ?


int rediriger_stdout(char * fichier){
	int fd1 = 0;
	if( (fd1 = open(fichier, O_RDWR)) == -1){
		perror("Erreur d'ouverture de fichier");
		return errno;
	}
	if(dup2(fd1, STDOUT_FILENO) == -1){
		perror("La destination n'est pas un descripteur valide");
		return errno;
	}
	return 1;
}

int restaurer_stdout(int fdStdout){
	if(dup2(fdStdout, STDOUT_FILENO) == -1){
		perror("La destination n'est pas un descripteur valide");
		return errno;
	}
	return 1;
}

int main(int argc, char * argv[]){
	int cpStdout = 0;

	if(dup2(cpStdout, STDOUT_FILENO) == -1){
		perror("La destination n'est pas un descripteur valide");
		return errno;
	}
	
	if(argc != 2){
		perror("Le seul argument contient le nom d'un fichier");
		return EXIT_FAILURE;
	}
	printf("print 1\n");	
	rediriger_stdout(argv[1]);
	printf("print 2\n");
	restaurer_stdout(cpStdout);
	printf("print 3\n");
	
	
	close(cpStdout);
	return 0;
}
