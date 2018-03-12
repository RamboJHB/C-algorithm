//create a standard thread()attribut

//#define_POSIX_SOURCE 1
#include <stdio.h>   
#include <pthread.h> 
#include <stdlib.h>   
#include <unistd.h>

pthread_mutex_t mutex =
PTHREAD_MUTEX_INITIALIZER;
int cont=0;


void *test(void *arg){
	int i;
	printf("Arg recieved %ds,tid:%d\n",(char*)arg,(int)pthread_self());
	for(i=0;i<100;i++){
		printf("end of thread %d\n",(int)pthread_self());
	}
	return NULL;
}


int main(int argc, char** argv){
	int i,N,ret;
	int *pt;
	pthread_t tid[N];
	pthread_attr_t attr;


	for(i=0;i<N;i++){
		if(pthread_attr_init(&attr)!=0){
			perror("pthread init attributs\n");
			exit(1);
		}
		if(pthread_create(&tid,&attr,test,"HELLO!")!=0){
			perror("pthread_create\n");
			exit(1);
		}
	}

	for(i=0;i<N;i++){
		pthread_join(tid[i],(void**)pt_ret);
		free(pt_ret);
	}

	sleep(3);
	printf("end of thread main\n");
	return EXIT_SUCCESS;

}

  
int main(){
	int i,j,k;
	for(i=0;i<=3;i++){		 
		for(j=0;j<=2-i;j++)	
			printf(" ");
			for(k=0;k<=2*i;k++)
				printf("*");
			printf("\n");
	}

	for(i=0;i<=2;i++){
		for(j=0;j<=i;j++)
			printf(" ");
		for(k=0;k<=4-2*i;k++)
			printf("*");
	printf("\n");
	}
}
