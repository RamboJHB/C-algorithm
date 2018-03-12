#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>


int main (int argc,char **argv){
  
  printf("i am : %d\n",(int)getpid());
  
  pid_t pid=fork();
  printf("fork returned :%d\n",pid);
  if(pid<0){
    perror("fork failed\n");
  }
  if(pid==0){
    printf("i am the child with :%d\n",getpid());
  }else if(pid>0){
    printf("i am the father with :%d\n",getpid());
  }
  return 0;
}
    
