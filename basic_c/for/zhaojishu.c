//输出a到b 的奇数

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
	for(i=a;i<=b;i=i+c){
		if(i%2==1){
			printf("%d ",i);
		}
	}

	printf("\n");
	return 0;	
}
