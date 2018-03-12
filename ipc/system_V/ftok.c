#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>

int main(int argc,char** argv){
    
    key_t key;

    if((key=ftok(".",'a'))==-1){
        perror("ftok creat key");
        exit(-1);
    }



}
