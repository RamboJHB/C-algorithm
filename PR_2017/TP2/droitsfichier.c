#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <errno.h> // int errno
#include <sys/stat.h> //stat()  macro of st_mode
#include <time.h>  //time
#include <string.h>

int main (int argc , char** argv){
    struct stat st;
    int n;
    printf("type right     hardlinks size last_change_time name\n");
    if (argc<2){
        printf("Usage : %s <file>\n",argv[0]);
        return -1;
    }
    if ((lstat(argv[1],&st))<0){
        printf("lstat %s failed : %s\n",argv[1],strerror(errno));
        return -1;
    }
    
    //type
    switch (st.st_mode & S_IFMT){         //other way without S_IFMT
        case S_IFREG:  printf("-");break; //if(S_ISREG(st.st_mode)) "-"
        case S_IFDIR:  printf("d");break; //..S_ISDIR.. putchar("d");
        case S_IFCHR:  printf("c");break; //S_ISCHR
        case S_IFBLK:  printf("b");break; //S_ISBLK
        case S_IFIFO:  printf("p");break; //S_ISFIFO
        case S_IFLNK:  printf("l");break; //S_ISLINK
        case S_IFSOCK: printf("s");break; //S_ISSOCK
    }
    printf("    ");
    //right
    for (n=8;n>=0;n--){
        if (st.st_mode &(1<<n)){//st_mode AND (1 left shift n)
            switch (n%3){            //
                case 2: printf("r");break; //right to read // 8/5/2 is 1
                case 1: printf("w");break; //right to write   7/4/1 is 1
                case 0: printf("x");break; //right to excute  6/3/0 is 1
            }
        }
        else{            // if(st.st_mode &(1<<n)==0)
            printf("-");
        }
    }
    //number of hard links
    printf(" %d",st.st_nlink);
    //size
    printf("         %lld",st.st_size);
    //last change time
    struct tm *tp;
    tp=localtime(&st.st_mtime);
    printf(" %d-%02d-%02d %02d:%02d",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday,tp->tm_hour,tp->tm_min);
    printf(" %s\n",argv[1]);
    printf("st.st_mode & S_IFMT-----for type\n");
    printf("for (n=8;n>=0;n--){if (st.st_mode &(1<<n switch(n%%3)012-----for right\n");
    return 0;
}

