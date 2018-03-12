#define _POSIX_SOURCE 1
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int count, val_1,val_2;
pthread_mutex_t lock;

void *test(void *arg){
  while(1){

#ifdef _LOCK_
    pthread_mutex_lock(&lock);
#endif 

    if(val_1!=val_2){
      printf("value_1=%d\tvalue_2=%d\n",val_1,val_2);
      sleep(1);
    }
#ifdef _LOCK_
    pthread_mutex_unlock(&lock);
#endif 
  }

}

int main(int argc,char** argv){
  pthread_t tid;
  if(pthread_mutex_init(&lock,NULL)!=0){
    perror("failed to init mutex");
    exit(-1);
  }
  if (pthread_create(&tid,NULL,test,NULL)!=0){
    perror("failed thread creation");
    exit(-1);
  }
  while (1){
    count++;

#ifdef _LOCK_
    pthread_mutex_lock(&lock);
#endif 

    val_1=count;
    sleep(1);
    val_2=count;

#ifdef _LOCK_
    pthread_mutex_unlock(&lock);
#endif 

  }
  return EXIT_SUCCESS;
}
