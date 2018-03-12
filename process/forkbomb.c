#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>


int main (int argc,char **argv){
  while (1){
    fork();
  }
  return 0;
}
    
