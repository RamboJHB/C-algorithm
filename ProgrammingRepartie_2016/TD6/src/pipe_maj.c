#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

/*Le père lit du clavier une chaîne de caractère qu'il passera au pipe, le fils récupère cette chaîne et l'affiche tout en majuscules*/

/*Penser à créer le pipe avant le fork*/

int main(int argc, char* argv[]){
	int TubeDesc[2], pid_fork, i = 0, nb_char;
	char buf[100];

	if(pipe(TubeDesc) == -1){
		perror("Erreur de création du pipe");
		return errno;
	}

	if((pid_fork = fork()) == -1){
		perror("Erreur de création du fils");
		return errno;
	}
	else if(pid_fork == 0){
		/*fils*/
		close(TubeDesc[1]);
		nb_char = read(TubeDesc[0], buf, sizeof(buf));
		for(i = 0; i < nb_char; i++){
			buf[i] = toupper(buf[i]);
		}
		write(STDOUT_FILENO, &buf[0], nb_char);
	}
	else{
		/*père*/
		nb_char = read(STDIN_FILENO, buf, sizeof(buf));

		close(TubeDesc[0]);
		write(TubeDesc[1], buf, nb_char);
		wait(NULL);
		printf("Fin du père\n");
	}

	return 0;

}
