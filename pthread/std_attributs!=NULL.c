#define _POSIX_SOURCE 1
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


void *test(void *arg){
    int i;
    printf("Argument recieved %s,tid: %d\n",(char*)arg,(int)pthread_self());
    for(i=0;i<10;i++){
        printf("end thread %d\t",(int)pthread_self());
    }
    return NULL;
}

int main(int argc,char** argv){
    pthread_t tid;
    pthread_attr_t attr;
    if (pthread_attr_init(&attr)!=0){
        perror("pthread init attributs\n");
    }
    if (pthread_create(&tid,&attr,test,"HELLO")!=0){  //pthread_create(&tid, &attr,xxx. xxx)
        perror("thread created \n");
        exit(1);
    }
    sleep(1);
    printf("end thread main\n");
    return EXIT_SUCCESS;
}
