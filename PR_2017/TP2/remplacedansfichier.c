#define _XOPEN_SOURCE 700
#include <stdlib.h> //macro EXIT_SUCCESS
//#include <sys/types.h>
#include <unistd.h> //read
#include <fcntl.h>  //open
#include <stdio.h>
#include <errno.h> // int errno
#include <string.h>
/*编写一个接收至少三个参数的程序：

  要创建的文件名;
  任何单词
  一系列未指定的单词。
  程序使用open创建文件。 
  然后，他将其余的单词，由空格分隔，在文件中，以及在输出流中，最后一个单词后跟一行。

  然后使用读取功能浏览同一个文件
  并在第一个空间播放停止。
  然后，我们用下面的单词替换第二个参数中给出的单词。 假设更换和更换的长度相同。*/
#define N 64

int main (int argc , char** argv){
  int fd, i = 1;
  char buf[N];
  size_t byte;

  if(argc < 3){
    fprintf(stderr,"command line : ./%s <dest_file> argv{1} ...\n",argv[0]);
    return errno;
  }
  if((fd = open(argv[1],O_CREAT|O_RDWR|O_APPEND)) < 0){
    perror("Open file failed");
    return errno;
  }
  //---------write in file--------------
  for(i = 2;i<argc;i++){
    //strcpy(buf, argv[i]);
    //strcat(buf, " ");
    if((byte = write(fd, argv[i], strlen(argv[i]))) == -1){
      perror("Write failed");
      return errno;
    }
    if((byte = write(fd," ", 1)) == -1){
      perror("Write failed");
      return errno;
    }
    printf("%s",buf);

  }
  //----------set offset----------------
  lseek(fd, 0, SEEK_SET);
  memset(buf, 0 ,strlen(buf));
  //---------print the a word in file ------------
  while((byte = read(fd, buf, 1)) != 0){;
    if(byte == -1){
      perror("Read failed");
      return errno;
    }
    if (strcmp(buf, " ") == 0){
      break;
    }
    fprintf(stdout, "%s", buf); 
  }
  printf("\n%s\n",buf);
  //---------print the whole file ------------
  //----------set offset----------------
  lseek(fd, 0, SEEK_SET);
  memset(buf, 0 ,strlen(buf));
  while((byte = read(fd, buf, 1)) != 0){
    if(byte == -1){
      close(fd);
      perror("Read failed");
      return errno;
    }
    printf("%s",buf); 
  }
  close(fd);
  return EXIT_SUCCESS;
}

