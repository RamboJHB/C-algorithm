#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
	pid_t pid;
	int  j=0; int i = 0;
	printf ("pid:%d-----------ancient\n", getpid());
	while (i < 3) {
		i ++;
		if ((pid = fork ()) == -1) {
				perror("fork");
				return errno;
		} 
		switch (i){
			case 1:
				if (pid == 0) {
					printf ("ppid:%d  pid:%d -- fils 1 rotation %i\n", getppid(), getpid(),i);
						j++;
				}
				break;
			case 2:
				if ((pid == 0) && (j == 0)){	
					printf ("ppid:%d  pid:%d -- fils 2 rotation %d j=%d\n", getppid(), getpid(),i,j);
					j++;
					continue;
				}
				if ((pid == 0) && (j == 1)){	
					printf ("ppid:%d  pid:%d -- fils 1.1 rotation %d j=%d\n", getppid(), getpid(),i,j);
					j++;
					return 0;
				}
				if ((pid != 0) && (j == 1)){wait(NULL); exit(1);}
				if ((pid != 0) && (j == 0)){continue;}			//continue : go to next rotation
				break;
			case 3:
				if ((pid == 0) && (j == 1)){
					printf ("ppid:%d  pid:%d -- fils 2.1 rotation %d j=%d\n", getppid(), getpid(),i,j);
						return 0;
				}else {
					wait(NULL);
					return 0;
				}
					break;		
		}
	}		
} 
