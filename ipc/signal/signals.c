#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void sig_handler(int sig_no, siginfo_t *info, void *ctext){
  printf("receive sig_no=%d\n",sig_no);
  if(sig_no == SIGQUIT){
    printf("haha,想退出了吗？");
  }else{
    printf("si_signo=%d\n",info->si_signo);
    printf("si_code =%d\n",info->si_code);
    printf("si_pid =%d\n",info->si_pid);
    printf("si_uid =%d\n",info->si_uid);
    printf("si_status=%d\n",info->si_status);
    //printf("si_utime =%lld\n",info->si_utime);
    //printf("si_stime =%lld\n",info->si_stime);
    printf("si_value =%d\n",info->si_value);
    printf("si_addr =0x%x\n",info->si_addr);
    //printf("si_fd  =%d\n",info->si_fd);
  }
  return ;
}
/*--------------------常用信号列表----------------------------*/
//SIGINT ctrl+c 
//SIGQUIT ctrl+\
//SIGPIPE 管道破裂
//SIGKILL 进程终止，不能被捕获
//SIGHUP shell退出
//SIGCHLD 子进程终止信号
//SIGFPE 浮点数异常(除以0之类的)
//SIGTERM 终止信号(kill pid)
int main(int argc ,char **argv){
  struct sigaction sa;
  sa.sa_flags  = 0;
  sa.sa_sigaction = sig_handler;
  sa.sa_flags  |= SA_SIGINFO;  //使用sa_sigaction作为回调
  //sa.sa_flags |= SA_RESETHAND; //处理函数只会被调用一次，之后被重置
  //sa.sa_flags |= SA_NOCLDSTOP; //如果安装了SIGCLD,子进程不是正常退出，而是被kill掉了，则不会通知
  //sa.sa_flags |= SA_NODEFER ;  //使对信号的屏蔽无效，即在信号处理函数执行期间仍能发出这个信号
  //sa.sa_flags |= SA_RESTART ;  //使被信号打断的系统调用自动重新发起
  //sa.sa_flags |= SA_NOCLDWAIT; //使父进程在它的子进程退出时不会收到 SIGCHLD 信号，这时子进程如果退出也不会成为僵尸进程
  //安装信号
  if(sigaction(SIGINT,&sa,NULL)==-1) printf("安装信号失败\n");
  if(sigaction(SIGQUIT,&sa,NULL)==-1) printf("安装信号失败\n");
  while(1){
    sleep(1);
  }
  return 0;
}
/*--------------------------信号编程相关结构体----------------------------------*/
 // struct sigaction {
 //   void (*sa_handler)(int);
 //   void (*sa_sigaction)(int, siginfo_t *, void *);
 //   sigset_t sa_mask;
 //   int sa_flags;
 //   void (*sa_restorer)(void);
 // }
// siginfo_t {
//    int   si_signo; /* Signal number */
//    int   si_errno; /* An errno value */
//    int   si_code;  /* Signal code */
//    pid_t  si_pid;  /* Sending process ID */
//    uid_t  si_uid;  /* Real user ID of sending process */
//    int   si_status; /* Exit value or signal */
//    clock_t si_utime;  //User time consumed 
//    clock_t si_stime; /* System time consumed */
//    sigval_t si_value; /* Signal value */
//    int   si_int;  /* POSIX.1b signal */
//    void *  si_ptr;  /* POSIX.1b signal */
//    void *  si_addr;  /* Memory location which caused fault */
//    int   si_band;  /* Band event */
//    int   si_fd;   /* File descriptor */
// }
// 信号    值      动作 解释
// SIGHUP  1          终端线路挂断
// SIGINT  2      Term  键盘输入的中断命令，从终端输入 Ctrl-C 时发生
// SIGQUIT 3      Core  键盘输入的退出命令
// SIGILL  4      Core  错误指令
// SIGABRT 6      Core  abort(3)发出的中止信号
// SIGFPE  8      Core  浮点数异常
// SIGKILL 9      Term  KILL信号
// SIGSEGV 11      Core  非法内存访问
// SIGPIPE 13      Term  管道断开
// SIGALRM 14      Term  alarm(2)发出的中止信号
// SIGTERM 15      Term  强制中止信号
// SIGUSR1 30,10,16   Term  用户自定义信号1
// SIGUSR2 31,12,17   Term  用户自定义信号2
// SIGCHLD 20,17,18   Ign  子进程中止信号
// SIGCONT 19,18,25   Cont  继续执行一个停止的进程
// SIGSTOP 17,19,23   Stop  非终端来的停止信号
// SIGTSTP 18,20,24   Stop  终端来的停止信号
// SIGTTIN 21,21,26   Stop  后台进程读终端
// SIGTTOU 22,22,27   Stop  后台进程写终端

