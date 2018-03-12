#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE_BUFFER 100

int main(int argc, char* argv[]){
	char buf[SIZE_BUFFER];
	if(argc != 3){
		printf("%s <file orig> <file dest>\n",argv[0]);
		return -1;
	}

	int fd1 = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_RDWR);
	if(fd1 == -1 || fd2 == -1){
		perror("error opening files");
		return EXIT_FAILURE;
	}
	int return_read = 0;
	while((return_read = read(fd1,buf, SIZE_BUFFER))>0){
		
		if(write(fd2,buf, return_read) == -1){
			perror("write");
			return EXIT_FAILURE;
		} 	
	} 

	if(return_read == -1){
		perror("read");
		return EXIT_FAILURE;	
	}
	close(fd1);
	close(fd2);
	return 0;
}
