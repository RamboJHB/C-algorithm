#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>


int main (int argc,char **argv){
  pid_t pid;
  FILE *fp;
  time_t t;
  int i,x,line ;
  char buf[64];
  printf("recording every () second\n");
  scanf("%d",&x);

  if ((pid=fork())<0)  {perror("fork failed");exit(-1);}
  //kill father
  if (pid>0){return 0;}    
  //set new sesion ,get rid of terminal
  if (setsid()==-1)  {/*perror("setsid failed");*/exit(-1);}
  //make new cwd 
  chdir("/tmp"); 
  //make new mask=0 
  if (umask(0)<0)   {perror("unmask failed");exit(-1);}
  //close father's file
  for(i=0;i<getdtablesize();i++){     
    close(i);
  }
  //fopen new float of file
  if((fp=fopen("/home/j/documents/c/linux_c/process/time.log","a+"))==NULL)
  {
    perror("failed fopen");exit(-1);
  }

  while (fgets(buf,64,fp)!=0){        //count lines already existed
    if(buf[strlen(buf)-1]=='\n')
      line++;
  }

  while(1){
    time(&t);
    fprintf(fp,"%d.%s",line++,ctime(&t));
    fflush(fp);
    sleep(x);
  }
}

