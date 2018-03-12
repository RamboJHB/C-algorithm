#include <stdio.h>
#include <errno.h>
#include <string.h>

int main (int argc , char** argv){
    //get a char:ch
    int count=0,ch=fgetc(stdin);
    printf("%c\n",ch);      //int ch printf %c ch

    //count how many char in a text
    FILE *fp;
    if ((fp=fopen(argv[1],"r"))==NULL){ //argv[1] si 1.txt: $./exe 1.txt
        perror("fopen error");
        return -1;
    }else {
        while ((ch=fgetc(fp))!=EOF){
            count++;
        }
    }
    printf("total %d\n",count);
    return 0;
}
