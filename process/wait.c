#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    int status;
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
        pid_t wai=wait(&status);
        printf("16 jin zhi :status=%x\n",status);
        printf("wait=%d\n",wai);
    }
    exit(EXIT_SUCCESS);
}




