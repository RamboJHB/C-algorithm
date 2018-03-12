#define _POSIX_SOURCE 700
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int fd1 = 0, i = 0, retour_read = 0;
	char tmp[100], espace[2] = " "; // utilisation pour strcmp
	//mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if(argc < 4){
		perror("Le nombre d'argument doit au moins être de 4; Le nom du fichier, un mot quelconque et une suite de mots quelconques");
		return EXIT_FAILURE;
	}
	
	if(strlen(argv[2]) != strlen(argv[4])){
		perror("Le remplaçant et le remplacé doivent être de même longueur");
		return EXIT_FAILURE;
	}


	//ATTENTION creat renvoie un descripteur du fichier qui ne permet que l'ecriture
	//avec open et O_CREAT si le fichier existe deja alors il sera ouvert avec le
	//descripteur au debut du fichier. Si on ajoute en plus l'option O_EXCL alors 
	//si le fichier existe deja une errno sera renvoyee
	if((fd1 = open(argv[1], O_CREAT|O_RDWR, 0644)) == -1){
		perror("Erreur ouverture du fichier");
		return errno;	
	}
	
	//on ecrit ici dans le fichier en concatenant des espaces entre chaque argument
	for(i =  3; i<argc; i++){
		printf("numéro : %d %s\n",i, argv[i]);
		strcpy(tmp, argv[i]);
		strcat(tmp, " ");
		if(write(fd1, tmp, strlen(tmp)) == -1){
			perror("Erreur d'écriture dans le fichier");
			return errno;
		}
	}
	
	//ici on lit dans le fichier et on veut s'arreter apres le premier mot lu, donc
	//premier espace, on remplace ce mot par le mot en deuxieme argument de meme longueur
	//en reecrivant directement dans le fichier avec le meme descripteur, les lettres 
	//seront ecrasees par les nouvelles
	lseek(fd1, 0, SEEK_SET);
	//N.B: Read n'efface pas le tampon, il ecrit directement dessus, il faut donc
	//faire attention a ce qu'il soit vide d'abord
	
	memset(tmp, 0, strlen(tmp)); //on vide le tmp
	printf("%s\n", tmp);
	while((retour_read = read(fd1, tmp, sizeof(char))) != 0){
		if(retour_read == -1){
			perror("Erreur de lecture du fichier");
			return errno;
		}

		if(strcmp(espace, tmp) == 0){
			printf("espace");
			write(fd1, argv[2], strlen(argv[2])); 
			break;
		}
		printf("%s\n", tmp);
	}	
	close(fd1);


	return 0;
}
