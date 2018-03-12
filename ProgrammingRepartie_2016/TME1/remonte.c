#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
//#include <wait.h>
#include <string.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("%s string <file orig> \n",argv[0]);
		return errno;	
	}	

	//	srand(time(NULL));
	int fd1 = open(argv[2], O_RDWR);
	if(fd1 == -1){
		perror("failed opening file ");
		return EXIT_FAILURE;
	}

	int n = atoi(argv[1]), i=0;
    pid_t pid;
	
	for(i=0; i<n; i++){
		if((pid = fork()) == -1){
			perror("fork");
			return errno;
		}
		else if(pid == 0){
			srandom(time(NULL));
			int randnum = (int) (10*(float) rand() / RAND_MAX);
			printf("%d\n", randnum);

			char randstr[100];
			int return_val = 0;
			sprintf(randstr,"%d", randnum);
			
			if((return_val= write(fd1,&randnum,sizeof(int))) == -1){
				perror("write");
				return EXIT_FAILURE;
			}
			exit(return_val);
		}
		else{
			int status=0, offset = 0;
			waitpid(pid,&status,0);
			if(WIFEXITED(status)){
				offset = WEXITSTATUS(status);
			}
			if(offset!=0){
				lseek(fd1, offset, SEEK_CUR);
			}
		}
	}
	
	lseek(fd1, 0, SEEK_SET);
	int return_read = 0, r = 0, total = 0;
	while((return_read = read(fd1, &r, sizeof(int))) > 0){
		total += r;
	} 
	printf("total : %d\n", total);
	close(fd1);
	return 0;
}
