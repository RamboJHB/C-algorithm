#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>

#define N 64

int main(int argc,char** argv){
    
    int shmid;
    char *addr;         //first address of attachment

    if((shmid=shmget(IPC_PRIVATE,512,0666))<0){
        perror("shmget");
        exit(-1);
    }

    if((addr=(char*)shmat(shmid,NULL,0))==(char*)-1){
        perror("shmat");
        exit(-1);
    }
    fgets(addr,512,stdin);

    shmdt(addr);
    return 0;
}
