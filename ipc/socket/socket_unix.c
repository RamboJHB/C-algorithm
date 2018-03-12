#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

int main (int argc,char **argv){

    int fd=-1;
    if((fd=socket(AF_UNIX,SOCK_STREAM,0))==-1){
        perror("socket");
        exit(-1);
    }
    /*1. fill the struct sockaddr_un*/
    struct sockaddr_un sunix;
    memset(&sunix,'\0',sizeof(struct sockaddr_un));//fill memory with a constant byte
    sunix.sun_family=AF_UNIX;         //type local
    strcpy(sunix.sun_path,"./Mysocket");
    
    /*2.  now bind*/
    if (bind(fd,(struct sockaddr *)&sunix,sizeof(sunix))==-1){
        perror("bind");
        exit(-1);
    }
    


    return 0;

}
