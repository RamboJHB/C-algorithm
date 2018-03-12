#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>


int main (int argc,char **argv){
  int x=5,y=2,z=30;
  printf("printf1 I am %d from %d x=%d y=%d z=%d\n",getpid(),getppid(),x,y,z);
  sleep(1);
  x=fork();
  printf("printf2 I am %d from %d x=%d y=%d z=%d\n",getpid(),getppid(),x,y,z);
  sleep(1);
  y=fork();
  printf("printf3 I am %d from %ld x=%d y=%d z=%d\n",getpid(),getppid(),x,y,z);
  sleep(1);
  z=fork();
  printf("printf4 I am %d from %ld x=%d y=%d z=%d\n",getpid(),getppid(),x,y,z);
  sleep(1);
  return 0;
}
    
