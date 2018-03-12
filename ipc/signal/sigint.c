#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char *argv[]){
    
    sigset_t sig;

    printf("BEGIN\n");
    
    sigemptyset(&sig);
    
    sigaddset(&sig, SIGINT);

    //sigprocmask(SIG_BLOCK, &sig, NULL);
    sigprocmask(SIG_SETMASK, &sig, NULL);
    kill(getpid(),SIGINT);
    printf("sleeping\n");
    sigpending(&sig);    
    if (sigismember(&sig, SIGINT)){
        printf("signal suspending\n");
    }
    sleep(10);
    printf("wake up\n");
    sigprocmask(SIG_UNBLOCK, &sig, NULL);

    printf("END");
    return EXIT_SUCCESS;
}  

