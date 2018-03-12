#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	struct stat stat_info1;
	struct stat stat_info2;
	if(argc != 3){
		perror("Nombre d'argument doit etre deux chemins vers des fichiers");
		return EXIT_FAILURE;
	}
	if(lstat(argv[1], &stat_info1) == -1 || lstat(argv[2], &stat_info2) == -1){
		perror("Erreur stat fichiers");
		return EXIT_FAILURE;
	}
	if(stat_info1.st_ino == stat_info2.st_ino)
		printf("fichiers identiques\n");
	else
		printf("fichiers différents\n");
	
	return 0;
}
