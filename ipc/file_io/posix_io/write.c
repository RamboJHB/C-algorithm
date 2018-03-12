#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>           //posix i/o

int main (int argc , char** argv){
    int fd;
    char buf[20];
    if (argc<2){
        printf("error:%s (Usage %s <file name>)\n",strerror(errno),argv[0]);            //strerror show success here!!!
        return -1;
    }
    if ((fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666))<0){
        perror("open error");
        return -1;
    }
    while ((fgets(buf,20,stdin))!=NULL){
        if (strcmp(buf,"quit\n")==0){    //\n is in the buf //stcmp =0 thenits the same
            break; 
        }
        write(fd,buf,strlen(buf));      //strlen():only write the string in buf
    }
    return 0;
}
