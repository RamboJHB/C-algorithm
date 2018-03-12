#include <stdio.h>
#include <errno.h>
#include <string.h>

#define N 64 

int main (int argc , char** argv){

    FILE *fp;
    char buf[N]={0};

    //open a stream 
    if (argc<2){
        printf("usage : %s <src_file>\n",argv[0]);
        return -1;
    }
    if ((fp=fopen(argv[1],"a+"))==NULL){   
        perror("fopen source file error");
        return -1;
    }

    
    int year=2016,month=10,date=26;
    fprintf(fp,"year:%d month %d date %d this is from fprintf\n",year,month,date); 
//    sprintf(buf,"year:%d month %d date %d\n",year,month,date); 
    fclose(fp);
    return 0;
}
