#define _XOPEN_SOURCE 700   

#include <stdio.h>
#include <fcntl.h> 	//open()
#include <unistd.h>	//close()
#include <stdlib.h>	//return EXIT_SUCCESS;
#include <errno.h>

#define N 64 

int main (int argc,char** argv){
    int fdd ,fdr;
	//char buf[N]={0};
	//char buf[N]={'\0'};
	char buf[N];
	buf[0]='\0';

	ssize_t r;
	ssize_t w;
	if (argc != 3){	
		printf("Usage : %s <source file> <destination file> \n",argv[0]);
		perror("");
		return EXIT_FAILURE;
	
	}
	if ((fdr = open(argv[1],O_RDONLY)) < 0){	
		close(fdr);
		perror("Open() failed");	//Bad file descriptor
	}
	if ((fdd = open(argv[2],O_CREAT|O_WRONLY|O_TRUNC)) < 0 ){	
		close(fdd);
		perror("Open() failed");
	}
	
	while((r = read(fdr,buf,N)) > 0){	
        buf[r]='\0';
        printf("%s",buf);
		w = write(fdd,buf,r);	/*write size :return value of read*/
//		printf("read %ld byte\twrite %zd byte\n",r,w);
	}
	if (r < 0 )	return errno;
	close(fdd);
	close(fdr);
	return EXIT_SUCCESS;
}
