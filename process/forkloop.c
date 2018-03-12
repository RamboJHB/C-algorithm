#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>


int main (int argc,char **argv){
  const int forktimes=2;
  for (int i=1;i<=forktimes;i++){
    fork();
    printf("pid %d from %d, loop :%d \n",getpid(),getppid(),i);
  }
  sleep(1);
  printf("-->pid %d from %d\n",getpid(),getppid());
  sleep(1);
  return 0;
}
    
