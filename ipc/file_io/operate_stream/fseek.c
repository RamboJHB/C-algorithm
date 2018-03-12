#include <stdio.h>
#include <errno.h>
#include <string.h>

int main (int argc , char** argv){
    FILE *fp;
    if ((fp=fopen(argv[1],"r+"))==NULL)
    {
        printf("fopen %s error: %s\n",argv[1],strerror(errno));
        return -1;
    }
    fseek(fp,0,SEEK_END);
    fputs("fseek got your position\n",fp);
    return 0;
}
