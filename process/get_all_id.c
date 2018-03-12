#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>



int main(int argc,char **argv)
{
  struct passwd {
        char *pw_name;      // 登录名称 
        char *pw_passwd;    // 登录口令 
        uid_t pw_uid;       // 用户ID 
        gid_t pw_gid;       // 用户组ID 
        char *pw_gecos;     // 用户的真名 
        char *pw_dir;       // 用户的目录 
        char *pw_shell;     // 用户的SHELL 
    };

    pid_t my_pid;           //pid
    pid_t parent_pid;       //ppid
    uid_t my_uid;           //uid
    uid_t my_euid;          //effective uid
    gid_t my_gid;           //gid
    gid_t my_egid;          //effective gid

    struct passwd *my_info;
    my_pid=getpid();
    parent_pid=getppid();
    my_uid=getuid();
    my_euid=geteuid();
    my_gid=getgid();
    my_egid=getegid();
    my_info=getpwuid(my_uid);

    printf("Process ID：%ld\n",my_pid);
    printf("Parent ID：%ld\n",parent_pid);
    printf("User ID：%ld\n",my_uid);
    printf("Effective User ID：%ld\n",my_euid);
    printf("Group ID：%ld\n",my_gid);
    printf("Effective Group ID：%ld\n",my_egid);
    if(my_info)
    {
        printf("My Login Name：%s\n" ,my_info->pw_name);
        printf("My Password ：%s\n" ,my_info->pw_passwd);
        printf("My User ID ：%ld\n",my_info->pw_uid);
        printf("My Group ID ：%ld\n",my_info->pw_gid);
        printf("My Real Name：%s\n" ,my_info->pw_gecos);
        printf("My Home Dir ：%s\n", my_info->pw_dir);
        printf("My Work Shell：%s\n", my_info->pw_shell);
    }
    return 0;
}
