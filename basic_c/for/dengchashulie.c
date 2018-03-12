//输出a到b 的等差数列 差为c

#include <stdio.h>

int main(){
	int a,b,c,i;
	printf("count from:");
	scanf("%d",&a);
	printf("to:");
	scanf("%d",&b);
	printf("growth by:");
	scanf("%d",&c);
	if(a>b){
		int t=b;
		b=a;
		a=t;
	}
	for(i=a;i<=b;i+=c){
		printf("%d ",i);
	}
	printf("\n");
	return 0;	
}
