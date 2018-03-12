#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>      // int open()     //posix i/o
//#include <unistd.h>       //?

int main (int argc , char** argv){
    int fd,total=0;
    size_t n = 0;
    char buf[64];
    if (argc<2){
        printf("error:%s (Usage %s <file name>)\n",strerror(errno),argv[0]);            //strerror show success here!!!
        return -1;
    }
    if ((fd=open(argv[1],O_RDONLY))<0){
        perror("error");
        return -1;
    }
    while ((n=read(fd,buf,64))>0){
        total+=n;
    }
    printf("read %d bytes\n",total);
    printf("file descriptor %d \n",(int)fd);
    return 0;
}
