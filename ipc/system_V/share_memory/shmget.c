#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>

int main(int argc,char** argv){
    
    int shmid;

    if((shmid=shmget(IPC_PRIVATE,512,0666))<0){
        perror("shmget");
        exit(-1);
    }



}
