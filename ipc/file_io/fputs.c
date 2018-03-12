#include <stdio.h>
#include <errno.h>
#include <string.h>

int main (int argc , char** argv){
    //puts 
    puts("puts out this with stdout\n");

    //test argc
    if (argc<2){
        printf("error \n");
        return -1;
    }
    //write "Hello world" to buf //add these in a file with fputs
    char buf[]="Hello world\n";
    FILE *fp;
    if ((fp=fopen(argv[1],"a"))==NULL){
        perror("fopen error");
        return -1;
    }else {
        fputs(buf,fp);
    }
    return 0;
}
