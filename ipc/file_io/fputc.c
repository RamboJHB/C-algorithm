#include <stdio.h>
#include <errno.h>
#include <string.h>

int main (int argc , char** argv){
    //put 'a'to a stream //here is print 'a'
    fputc('a',stdout);
    printf("\n");

    //test argc
    if (argc<2){
        printf("error \n")
        return -1;
    }
    //write 'a' to 'z' in stream//in a file
    int ch;
    FILE *fp;
    if ((fp=fopen(argv[1],"w"))==NULL){
        perror("fopen error");
        return -1;
    }else {
        for  (ch='a';ch<='z';ch++){
            fputc(ch,fp);
        }
    }
    return 0;
}
