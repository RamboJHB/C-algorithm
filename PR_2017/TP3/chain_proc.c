#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h> //fork()
#include <sys/types.h>//wait()
#include <sys/wait.h>//wait()

/*使用fork函数，编写一个创建进程链的程序，以便初始进程（手动进程）创建一个进程，反过来又创建一个进程，依此类推，直到创建N过程（除初始过程之外）。

在创建时，链中的最后一个过程显示所有其他进程的Pid，包括初始进程的进程。

每个其他进程等待他的儿子完成，然后在结束之前显示自己的Pid（使用getpid），他的父亲（使用getppid）和他的儿子。

还希望最后创建的进程绘制0到100之间的随机值，并将其作为输出状态传递给其父进程。使用等待及其宏，使父亲获得此状态，初始过程在结束前显示。
*/

int main(int argc, char* argv[]){
    int j = 0, i = 0, N, state = 0, return_val;
    time_t t;
    pid_t pid;
    // int* pids;

    if(argc != 2){
        fprintf(stderr, "%s N",argv[0]);
        return errno;
    }

    N = atoi(argv[1])+1;
    //pids = malloc(N * sizeof(int));
    static int pids[64];
    pids[0] =  getpid();
    printf("Main pid = %d\n",pids[0]);    

    while(i < N ){
        if((pid = fork()) < 0){
            perror("Fork() failed");
            return errno;
        }
        //-----------father process-------------
        if(pid > 0){
            waitpid(pid , &state, 0);
            if (WIFEXITED(state)){
                return_val = WEXITSTATUS(state);
            }
            printf("end Proc %d : ppid = %d - pid = %d <<<%d<<< childpid = %d\n",i,getppid(),getpid(),return_val,pid);
            exit(return_val);
        }
        //------------child process---------------
        if(pid == 0){
            if (i != 0){
                pids[i] = getpid();
            }
            if(i == (N-1) ){
                printf("Proc %d : ",i);
                for (j = 0;j<N;j++){
                    printf("%d ",pids[j]);
                }
                printf("\n");
                srand((unsigned)time(&t)%getpid());
                int random_val = rand()%100;
                exit(random_val);
            }
        }
        i++;
    }
    //free(pids);
    return EXIT_SUCCESS;
}
