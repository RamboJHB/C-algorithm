#include <stdio.h>
#include <errno.h>
#include <string.h>

int main (int argc , char** argv){
    FILE *fp;
    if ((fp=fopen(argv[1],"r+"))==NULL){
        perror("fopen error");
        printf("fopen %s error: %s\n",argv[1],strerror(errno));
        return -1;
    }
    return 0;
}
