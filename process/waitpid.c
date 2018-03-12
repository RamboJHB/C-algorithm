#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    int status_wait;
    int status_waitpid;
    pid_t pid;

    if ((pid=fork())<0) {
        fprintf(stderr, "fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid==0){
        sleep(1);
        exit(2);
    }
    else if (pid>0){
      //only one success here
        pid_t val_wait=wait(&status_wait);
        pid_t val_waitpid=waitpid(-1,&status_waitpid,0);

        printf("16 jin zhi :status_wait=%x\n",status_wait);
        printf("16 jin zhi :status_waitpid=%x\n",status_waitpid);

        printf("child process exit(%d) wait\n",WEXITSTATUS(status_wait));
        printf("child process exit(%d) waitpid\n",WEXITSTATUS(status_waitpid));

        printf("wait=%d\n",val_wait);
        printf("waitpid=%d\n",val_waitpid);
    }
    exit(EXIT_SUCCESS);
}


int print_bin(int n)
{
    int l = sizeof(n)*8;//总位数。
    int i;
    if(i == 0)
    {
        printf("0");
        return 0;
    }
    for(i = l-1; i >= 0; i --)//略去高位0.
    {
        if(n&(1<<i)) 
            break;
        }
        for(;i>=0; i --)
            printf("%d", (n&(1<<i)) != 0);
    printf("\n");
}

