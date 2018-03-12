#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int lecture_posix(char * fichier){
    pid_t pid_fork = 0;
    long retour_read = 0;
    char buffer[2];
    int fd1 = 0;
    if((fd1 = open(fichier, O_RDONLY, S_IREAD)) == -1){
        perror("L'ouverture du fichier a échoué");
        return errno;
    }
    if( (pid_fork = fork()) == 0){
        if(fork()== -1){
            perror("Erreur de la création du petit fils");
            return errno;
        }
    }
    else if (pid_fork == -1){
        perror("Echec de la création du fils");
        return errno;
    }
    
    while((retour_read = read(fd1, buffer ,1)) != 0){
        if(retour_read == -1){
            perror("Erreur de lecture du fichier");
            return errno;
        }
        printf("Le caractère %s a été lu par %d\n", buffer, getpid());
    }
    
    return 1;
}
//attention fgetc retourne un int
int lecture_c(char * fichier){
    FILE * fic;
    int c;
    pid_t pid_fork = 0;
    fic = fopen(fichier, "r");
    if(fic == NULL){
        perror("Le fichier specifie n'existe pas ou il n'a pas pu etre ouvert");
        return errno;
    }
    
    if( (pid_fork = fork()) == 0){
        if(fork()== -1){
            perror("Erreur de la création du petit fils");
            return errno;
        }
    }
    else if (pid_fork == -1){
        perror("Echec de la création du fils");
        return errno;
    }
    
    while( (c=fgetc(fic)) != EOF){
        printf("Le caractere %c a ete lu par %d\n", c, getpid());
        sleep(1);
    }
    return 1;
    
}

int main(int argc, char * argv[]){
    if(argc != 3){
        perror("2 arguments are requiredé, option -p or -C ");
        return EXIT_FAILURE;
    }
    
    if(strcmp(argv[1], "-p") == 0){
        lecture_posix(argv[2]);
    }
    else if(strcmp(argv[1], "-C") == 0){
        lecture_c(argv[2]);
    }
    else{
        perror("the first argument is required to be either -p or -C");
        return EXIT_FAILURE;
    }
    
    return 0;
}

