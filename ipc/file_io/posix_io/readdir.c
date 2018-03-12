#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>      // int open()     //posix i/o
#include <dirent.h>

int main (int argc , char** argv){
    DIR *dirp;
    struct dirent *dp;
    if (argc<2){
        printf("Usage : %s <directory>\n",argv[0]);
        return -1;
    }
    if ((dirp=opendir(argv[1]))==0){
        printf("opendir %s error : %s\n",argv[1],strerror(errno));
        return -1;
    }
    while ((dp = readdir(dirp))!=NULL)
    {   
        printf("%s\n",dp->d_name);
    }
    return 0;
}
