//求最大数

#include <stdio.h>

int main(){
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
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
