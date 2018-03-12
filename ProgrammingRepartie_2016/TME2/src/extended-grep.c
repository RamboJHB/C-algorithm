#define _XOPEN_SOURCE 700
#define _POSIX_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
int main(int argc, char* argv[]){
	DIR * argument;
	struct dirent * infoFichier; /*ne pas oublier struct quand on declare une variable de type dirent*/
	char * tmp;
	int cpt = 0;

	if(argc != 3){
		perror("Le nombre d'argument doit etre de deux, le caractere a rechercher et le dossier dans lequel chercher");
		return EXIT_FAILURE;
	}

	/*opendir retourne null en cas d'erreur sinon retourne un pointeur vers le flux de repertoire*/
	
	if ((argument = opendir(argv[2])) == NULL){
		perror("Erreur d'ouverture du fichier");
		return errno;
	}	

	/* 
	 * readdir retourne null s'il n'y a plus de fichiers dans le repertoire ou dans le cas d'une erreur
	 * pour differencier les deux cas, errno est modifie dans le cas d'une erreur. Nous mettons alors 
	 * errno a zero puis testons si sa valeur a changee pour detecter l'erreur.
	 */
	errno = 0;
	while((infoFichier = readdir(argument)) != NULL){
		if(errno != 0){
			perror("Erreur a la lecture d'un fichier du repertoire");
			return errno;
		}
		if((tmp = strstr(infoFichier->d_name, argv[1])) != NULL){
			printf("Fichier correspondant : %s\n", infoFichier->d_name);
			cpt++;
		}
		tmp = NULL;
		/*printf("Fichier : %s\n", infoFichier->d_name);*/
	}
	if(cpt == 0){
		printf("Aucun fichier valide \n");
	}

	closedir(argument);
	return EXIT_SUCCESS;
}
