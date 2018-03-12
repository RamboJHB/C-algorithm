// 求一个等差数列和

#include <stdio.h>

int main(){
	int a,b,c,i,sum=0;
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
		printf("%d ",i);
		sum=sum+i;
	}
	printf("sum is:%d\n",sum);
	return 0;	
}
