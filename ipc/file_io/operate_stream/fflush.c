#include <stdio.h>
#include <errno.h>
#include <string.h>

int main (int argc , char** argv){
    FILE *fp;
    if ((fp=fopen(argv[1],"a"))==NULL)
    {
        printf("fopen %s error: %s\n",argv[1],strerror(errno));
        perror("error");
        return -1;
    }
    fputs("from fflush\n",fp);
    //fflush(fp);
    while (1);
    return 0;
}
