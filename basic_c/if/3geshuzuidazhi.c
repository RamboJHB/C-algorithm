// 求三个数字最大值

#include <stdio.h>

int main(){
	int b,c,a;
	printf("please enter the first integer:");
	scanf("%d",&a);
	printf("please enter the second integer:");
	scanf("%d",&b);
	printf("please enter the third integer:");
	scanf("%d",&c);
	float d=(a+b+c)/3.;
	if(b>a){
		a=b;
	}
	if(c>a){
		a=c;
	}
	printf("the biggest number is:%d\n",a);
	printf("the average is:%f\n",d);
	return 0;	
}
