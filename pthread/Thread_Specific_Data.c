#define _POSIX_SOURCE 1
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char message[32]="A Message";

void *test(void *arg){
    sleep(1);
    strcpy(message,"message is marked by thread hahaha");
    printf("tid:%d recieve argument:%s\n",(int)pthread_self(),(char*)arg);
    printf("tid:%d end thread\n",(int)pthread_self());
    pthread_exit("i am a string in pthread_exit() ");
}
int main(int argc,char** argv){
    pthread_t tid;
    void *result;
    pthread_attr_t attr;
    if (pthread_create(&tid,NULL,test,"HELLO")!=0){
        perror("thread created \n");
        exit(-1);
    }
    printf("in main message is :%s\n",message);
    pthread_join(tid,&result);
    printf("recieve result:%s \n(by pthread_join)\n",result);
    printf("after thread messege is :%s\n",message);
    sleep(1);
    printf("end thread main\n");
    return EXIT_SUCCESS;
}
