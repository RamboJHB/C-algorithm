#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char* argv[])
{
  for (int i=0;i<argc;i++){
    printf("argc=%d argv[%d]=%s *arg[]=%d\n",argc,i,argv[i],*argv[i]);
  }
  return 0;
}
