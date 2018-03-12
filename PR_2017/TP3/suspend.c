#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h> //fork()
#include <sys/types.h>//wait()
#include <sys/wait.h>//wait()

/*我们重复以前的练习，但我们不要使用等待和类似的功能。 
 * 相反，我们将使用sigsuspend系列的功能。 
 * 确保在所有其他方式创建之前没有任何过程结束，才能解决问题？ 
 * 在他的儿子创造1秒后，等待他的信号之前，每个进程都不会丢失任何信号。
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
