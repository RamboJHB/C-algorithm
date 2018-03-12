#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>      // int open()     //posix i/o
int main (int argc , char** argv){
    int fd;
    if ((fd=open("open.txt",O_RDWR|O_CREAT|O_EXCL,0666))<0){
        if (errno==EEXIST){
            perror("existed error");
        }else{
            perror("other error");
        }
        return -1;
    }
    return 0;
}
