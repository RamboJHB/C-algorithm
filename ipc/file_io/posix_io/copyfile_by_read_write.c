#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define N 64 

int main (int argc , char** argv){

    int  fds,fdd;
    char buf[N]={0}; 
    ssize_t bytes;  
    int a;

    if (argc<3){
        printf("usage : %s <src_file> <dst_file>\n",argv[0]);
        return -1;
    }
    if ((fds=open(argv[1],O_RDONLY))<0){    //打开源文件
        close(fds);
        fprintf(stderr,"open %s : %s \n",argv[1],strerror(errno));
        return -1;
    }
    if ((fdd=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666))<0){   //打开目标文件
        close(fdd);
        fprintf(stderr,"open %s : %s \n",argv[2],strerror(errno));
        return -1;
    }
    while ((bytes=read(fds,buf,N))>0){       //以字符为单位读取1字节
                                          //缓冲区有64字节所以有64个对象
        a=write(fdd,buf,bytes);
        printf("copy %d bytes paste %d bytes\n",bytes,a);
    }
    close(fds);
    close(fdd);
    return 0;
}
