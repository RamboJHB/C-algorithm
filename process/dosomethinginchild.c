#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

void dosomething(char* name,int y);

void print_bin(int n);

int main (int argc,char **argv){
  int i=0;  
  int x,y;
  printf("child exit() with(0-255):\n");
  scanf("%d",&x);
  printf("child sleep() :\n");
  scanf("%d",&y);
  pid_t pid=fork();
  if(pid<0){
    perror("fork failed\n");
  }
  if(pid==0){
    printf("-->pid %d\tchild fork returned 0\n",getpid(),pid);
    dosomething("child",y);
    exit(x);
  }else if(pid>0){
    printf("pid %d\tfather fork returned %d\n",getpid(),pid);
    printf("pid %d\twaiting for child %d\n\n",getpid(),pid);
//    dosomething("father",y);
  }
    
  int status=0;
  //pid_t pidchild= wait(&status);
  printf("\npid %d\tget pid_child=wait=%d\n",getpid(),wait(&status));

  printf("pid %d\tfinished with status= ",getpid()); 
  print_bin((int) status);
  printf("pid %d\t my child returned %d\n",getpid(),WEXITSTATUS(status));
  printf("pid %d father exiting\n",getpid());
  return 0;

}

void dosomething(char* name,int y){
  const int NUM_TIME=3;
  int i,a=1;
    if(name=="child"){                   //name="" 
      for (i=1;i<=NUM_TIME;i++){
        a++;
        sleep(rand()%y);
        printf("-->pid %d\t%s done pass: %d\ta=%d\n",getpid(),name,i,a);
      }
    }
    else if(name=="father"){
      for (i=1;i<=NUM_TIME;i++){
        a*=10;
        sleep(rand()%4);
        printf("pid %d\t%s done pass: %d\ta=%d\n",getpid(),name,i,a);
      }
    }
}


void print_bin(int x)
{
    int i,j,a[100];
	printf("%d %x ",x,x);
	if(x==0){printf("0\n");return ;}
	
	//一下为十进制转换成其他进制的基本规则
	for(i=0;x!=0;i++){
		a[i]=x%2;
		x=x/2;      
	} 
	i--;         
	//如果要转换的进制大于十进制，要特别处理。
	for(j=i;j>=0;j--)
		printf("%d",a[j]);
	printf("\n");
	
	return;
}
