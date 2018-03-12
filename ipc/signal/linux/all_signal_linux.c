#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#define ARRAYLEN(arr) sizeof(arr) / sizeof((arr)[0])

static int signo_arr[] = {
    SIGABRT , SIGALRM  , SIGBUS,
    SIGCHLD , SIGCONT  , SIGFPE,
    SIGHUP  , SIGILL   , SIGINT,
    //SIGIO   , 
    SIGKILL  , SIGPIPE,
    SIGPROF , SIGQUIT  , SIGSEGV,
    SIGSYS  , SIGTERM  , SIGTRAP,
    SIGTSTP , SIGTTIN  , SIGTTOU,
    SIGURG  , SIGVTALRM, SIGUSR1,
    SIGUSR2 , SIGXCPU  , SIGXFSZ
};
int main(void) {
    int i = 0;
    int signo = -1;
    char *msg = "SIGNAL";

    for (i=0; i < ARRAYLEN(signo_arr); i++) {
        signo = signo_arr[i];
        printf("Signal[%d]: %s\n", signo, sys_siglist[signo]);
    }

	return EXIT_SUCCESS;
}  

