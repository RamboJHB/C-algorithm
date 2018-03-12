//求三个数字中位数

#include <stdio.h>

int main(){
	int b,c,average;
	printf("please enter the first integer:");
	scanf("%d",&average);
	printf("please enter the second integer:");
	scanf("%d",&b);
	printf("please enter the third integer:");
	scanf("%d",&c);
	float d=(average+b+c)/3.;
	if((c>b&&b>average)||(average>b&&b>c)){
		average=b;
	}
	if((b>c&&c>average)||(average>c&&c>b)){
		average=c;
	}
	printf("the average number is:%d\n",average);
	printf("the average is:%f\n",d);
	return 0;	
}
