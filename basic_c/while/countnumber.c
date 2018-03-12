//count from a to b

#include <stdio.h>

int main(){
	int b,a=1;
	printf("count from a to b :\n");
	printf("a:");
	scanf("%d",&a);
	printf("b:");
	scanf("%d",&b);
	if(a>b){
		int t=b;
		b=a;
		a=t;
	}
	while(a<=b){
		printf("%d ",a);
		a++;
	}
	printf("\n");
	return 0;
}
