#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT 5001
#define SERV_IP_ADDR "127.0.01"

int main (int argc,char **argv){

    /*1.  make socket with type of TCP*/
    int fd=-1;
    if((fd=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("socket");
        exit(-1);
    }
    /*2.   bind*/
    /*2.1. fill the struct socketaddr with socket_addr_in ipv4*/
    struct socketaddr_in sin;
    bzero(&sin,sizeof(sin));        //bzero() : fill with 0
    sin.sin_family=AF_INET;         //type ipv4
    sin.sin_port=htons(SERV_PORT);  //port number in network byte order
    //fill sin.sin_addr.s_addr
//    sin.sin_addr.s_addr=inet_addr(SERV_IP_ADDR);  //ezway just for ipv4
    if (inet_pton(AF_INET,SERV_IP_ADDR,(void*)&sin.sin_addr.s_addr)!=0){
        perror("inet_pton");
        exit(-1);
    }
    /*2.2.  now bind*/
    if (bind(fd,(struct sockaddr *)&sin,sizeof(sin))<0){
        perror("bind");
        exit(-1);
    }
    
    /*3.listen()  for connections on socket*/


    /*4.accept() wait for connections*/
    return 0;

}
