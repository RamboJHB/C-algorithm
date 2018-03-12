#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

static void *sig_thread(void *arg)
{
    sigset_t *set = (sigset_t *)arg;
    int err = -1, signo = -1;

    for(;;) {
        if(0 != (err = sigwait(set, &signo))) {
            printf("sigwait error\n");
            exit(1);
        }
        printf("Get signal[%d]: %s\n",
               signo, sys_siglist[signo]);
    }
}

int main(int argc, char *argv[])
{
    pthread_t thread;
    sigset_t sig_set;
    int err = -1;

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGQUIT);
    sigaddset(&sig_set, SIGUSR1);
    /* set signal handler thread sigmask */
    err = pthread_sigmask(SIG_BLOCK, &sig_set, NULL);
    if(0 != err) {
        printf("set pthread_sigmask error\n");
        goto Error;
    }
    /* create signal thread */
    err = pthread_create(&thread, NULL,
                         &sig_thread, (void *)&sig_set);
    if (0 != err) {
        printf("create pthread error\n");
        goto Error;
    }

    pause();
Error:
    return err;
}
