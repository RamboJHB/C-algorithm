//n numbers' average

#include <stdio.h>

int main(){
	int number,n=0,sum=0;
	double average;
	printf("Please enter a number(enter 0 to quit) :");
	scanf("%d",&number);
	while(number!=0){
		sum=sum+number;
		n=n+1;
		scanf("%d",&number);	
	}
	
	average=(double)sum/n;
	printf("sum is %d.average is %f\n",sum,average);
	return 0;
}
