//write data to buffer& read data to buffer
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char buffer[32];
sem_t sem_w;    //right now buffer is writable
sem_t sem_r;    //right now buffer is readable

void *readbuf(void *arg){
    while (1){
        sem_wait(&sem_r);
        printf("you entered %d characters\n",strlen(buffer)-1);
        sem_post(&sem_w);
        if(strncmp(buffer,"quit",4)==0)
            pthread_exit(0);
    }
}
void *writebuf(void *arg){
    while(1){
        sem_post(&sem_w);
        fgets(buffer,32,stdin);
        sem_post(&sem_r);
        if(strncmp(buffer,"quit",4)==0)
            pthread_exit(0);
    }
}
int main(int argc,char** argv){
    pthread_t write_buf;
    pthread_t read_buf;
    void *result;

    if (sem_init(&sem_r,0,0)<0){    //buffer is empty is not readable
        perror("sem_init");
        exit(-1);
    }
    if (sem_init(&sem_w,0,1)<0){    //buffer is empty its writable
        perror("sem_init");
        exit(-1);
    }
    if (pthread_create(&write_buf,NULL,writebuf,NULL)!=0){
        perror("pthread_create write failed");
        exit(-1);
    }
    if (pthread_create(&read_buf,NULL,readbuf,NULL)!=0){
        perror("pthread_create read failed");
        exit(-1);
    }
    printf("input 'quit' to exit\n");

    pthread_join(write_buf,NULL);
    pthread_join(read_buf,NULL);
    sem_destroy(&sem_w);    
    sem_destroy(&sem_r);    

    return EXIT_SUCCESS;
}
