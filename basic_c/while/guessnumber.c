//guess number

#include <stdio.h>

int main(){
	int a=6,b,i=0;
	//loop
	while(b!=a||i==0){
		printf("Please guess a number :"); // n+1 times
		scanf("%d",&b);                    // n+1 times
		i++;
		if(a<b){
			printf("Too big (%d try)\n",i);      //n times
		}else if(a>b){
			printf("Too small (%d try)\n",i);    //n times
		}
	}
	//endloop
	printf("Congratulations!\nYou have tried %d times.\n",i);

	return 0;
}
