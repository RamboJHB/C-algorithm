#include <stdio.h>
#include <errno.h>
#include <string.h>

int main (int argc , char** argv){

    FILE *fps,*fpd;
    int ch;
    if (argc<3){
        printf("usage : %s <src_file> <dst_file>\n",argv[0]);
        return -1;
    }
    if ((fps=fopen(argv[1],"r"))==NULL){ 
        perror("fopen source file error");
        return -1;
    }
    if ((fpd=fopen(argv[2],"w"))==NULL){ 
        perror("fopen direction file error");
        return -1;
    }
    while ((ch=fgetc(fps))!=EOF){
        fputc(ch,fpd);
    }
    fclose(fps);
    fclose(fpd);
    return 0;
}
