#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[]){
	struct stat stat_info;
	if(argc != 4){
		perror("Il doit y avoir trois arguments, le premier est le type d'opé, le deuxième est le nom du fichier, le troisième est le fichier à copier ou les nouveaux droits");
		return EXIT_FAILURE;
	}
	
	if(lstat(argv[2], &stat_info) == -1){
		perror("Récupération fichier, ou fichier inexistant");
		return EXIT_FAILURE;
	}

	if(S_ISDIR(stat_info.st_mode)){
		perror("Le fichier spécifié en second argument est un dossier");
		return EXIT_FAILURE;
	}

	
	//*argv[1] donne seulement le premier caractère de argv[1]	
	switch(*argv[1]){
		case 'E': 
		case 'e':
			if(unlink(argv[2]) == -1){
				perror("Effacement fichier échoué");
				return errno;
			}
			printf("Effacement effectué");
			break;
		case 'R':
		case 'r':
			if(rename(argv[2], argv[3]) == -1){
				perror("Rename échoué");
				return errno;
			}
			printf("Renommage effectué");
			break;
		case 'C':
		case 'c':
			if(*argv[3] == 'R' || *argv[3] == 'r'){
				if(chmod(argv[2], S_IRUSR) == -1){
					perror("Erreur changement droit lecture");
					return errno;
				}
			}
			if(*argv[3] == 'W' || *argv[3] == 'w'){
				if(chmod(argv[2], S_IWUSR) == -1){
					perror("Erreur changement droit écriture");
					return errno;
				}
			}
			printf("Changement de droits effectué");
			break;

	}
	return 0;
}
			
	

