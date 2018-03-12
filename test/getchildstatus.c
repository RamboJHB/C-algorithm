#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

int main(int argc,char** argv)
{
    pid_t child;
    int status;
    printf("This will demostrate how to get child status\n");
    if((child=fork())==-1)          //failed creating
    {
        printf("Fork Error ：%s\n",strerror(errno));
        _exit(1);
    }
    else if(child==0)               //child process
    {
        int i;
        printf("I am the child：%ld\n",getpid());
        for(i=0;i<1000000;i++) 
            sin(i);
            i=5;
        printf("I exit with %d\n",i);
     //   _exit(i);
    }
    while(((child=wait(&status))==-1)&(errno==EINTR));  //
        if(child==-1)
            printf("Wait Error：%s\n",strerror(errno));
        else if(!status)
            printf("Child %ld terminated normally return status is zero\n",child);
        else if(WIFEXITED(status))
            printf("Child %ld terminated normally return status is %d\n",child,WEXITSTATUS(status));
        else if(WIFSIGNALED(status))
            printf("Child %ld terminated due to signal %d znot caught\n",child,WTERMSIG(status));


    return 0;
}
