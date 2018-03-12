#define _XOPEN_SOURCE 700   

#include <stdio.h>
#include <fcntl.h> 	//open()
#include <unistd.h>	//close()
#include <stdlib.h>	//return EXIT_SUCCESS;
#include <errno.h>
#include <time.h>
#include <string.h>

#define N 64 

int main (int argc,char** argv){
	int fd=0, n, return_val=0;
	char buf[N];
	pid_t pid;
    time_t t;
    static int total=0;
	if (argc != 3){	
		printf("Usage : %s <number> <file name>\n",argv[0]);
		return EXIT_FAILURE;
	}
    n = atoi(argv[1]);
	if (n==0){
        printf("nothing\n");
		close(fd);    
        return EXIT_FAILURE;
    }
    if ((fd = open(argv[2],O_CREAT|O_RDWR|O_APPEND,0666)) == -1 ){	
		close(fd);
		perror("Open() failed");
		return EXIT_FAILURE;
	}
	
	for (int i=0;i<n;i++){        
		if ((pid=fork())== -1){
			perror ("fork() failed");
		    return EXIT_FAILURE;
		}
		if (pid==0){                        
			printf("pid:%d Im a fils\t",getpid());
            //to solve child process always get same random number
            srand((unsigned)time(&t)%getpid());
			int val = rand()%100;
			printf("write val= %d ",val);	
            sprintf(buf ,"%d", val);
			printf("buf=%s",buf);	
            strcat(buf," ");
            return_val = write(fd,buf,sizeof(char)*strlen(buf));
			printf(" %d bytes\n",(int)return_val);	
            //buf[0]='\0';
            close(fd);
            exit(return_val);
		}else{
            int status = 0, offset = 0;
	        waitpid(pid, &status, 0);
            if(WIFEXITED(status)){
                offset=WEXITSTATUS(status);
                //to see how many bytes in fd totally
                printf("read this time = %d\n", offset);
                total += offset;
            }
            if (offset != 0){
                lseek (fd, offset, SEEK_CUR);
            }
		}
	}
    printf("-------total read %d\n",total);
	close(fd);
	return EXIT_SUCCESS;
}
