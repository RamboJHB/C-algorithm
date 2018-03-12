#include <stdio.h>
#include <errno.h>
#include <string.h>

#define N 64 

int main (int argc , char** argv){

    FILE *fps,*fpd;
    char buf[N]={0};      //每次读取的对象个数
    ssize_t bytes;  
    int a;

    if (argc<3){
        printf("usage : %s <src_file> <dst_file>\n",argv[0]);
        return -1;
    }
    if ((fps=fopen(argv[1],"r"))==NULL){    //打开源文件
        perror("fopen source file error");
        return -1;
    }
    if ((fpd=fopen(argv[2],"w"))==NULL){    //打开目标文件
        perror("fopen direction file error");
        return -1;
    }
    while ((bytes=fread(buf,1,N,fps))>0){       //以字符为单位读取1字节
                                          //缓冲区有64字节所以有64个对象
        a=fwrite(buf,1,bytes,fpd);
        printf("copy %d bytes paste %d bytes\n",bytes,a);
    }
    fclose(fps);
    fclose(fpd);
    return 0;
}
