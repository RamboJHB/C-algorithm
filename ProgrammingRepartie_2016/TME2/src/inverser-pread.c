#define _XOPEN_SOURCE 700
#define _POSIX_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char * argv[]){
	int fdW = 0, fdR = 0, retour_write = 0; 
	off_t offset;
	char newFile[20] = "fichierPread.txt";
	char tmp;
	if(argc != 2){
		perror("Le programme prend en argument un nom de fichier");
		return EXIT_FAILURE;
	}

	/* Ne jamais utiliser access avant open
	 * On souhaite seulement tester l'existance du fichier dans lequel on va ecrire, on ne traite pas le cas -1
	 * 
	 */
	if(access(newFile, F_OK) == 0){
		if(unlink(newFile) == -1){
			perror("Erreur de destruction du fichier inverse");
			return errno;
		}
	}

	if((fdR = open(argv[1], O_RDONLY, 0644)) == -1 ){
		perror("Erreur d'ouverture du fichier passe en argument, ou erreur de creation du nouveau fichier");
		return errno;
	}

	if((fdW = open(newFile, O_CREAT|O_RDWR, 0644)) == -1){
		perror("Erreur d'ouverture du fichier passe en argument, ou erreur de creation du nouveau fichier");
		return errno;
	}	

	offset = lseek(fdR, (off_t) 0, SEEK_END);
	while(offset > 0){
		offset--;	
		if(pread(fdR, &tmp, sizeof(char), offset) == -1){
			perror("Erreur de lecture du fichier passe en argument");
			return errno;
		}
		if((retour_write = write(fdW, &tmp, 1)) == -1){
			perror("Erreur d'ecriture dans le nouveau fichier");
			return errno;
		}
		printf("retour_write : %d\n", retour_write);
		printf("Le caractere lu est %c\n" , tmp);
	}		

	close(fdR);
	close(fdW);

	return 0;
}
