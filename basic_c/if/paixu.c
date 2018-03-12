//三个数字从大到小排序


#include <stdio.h>

int main(){
	int a,b,c,t;
	scanf("%d%d%d",&a,&b,&c);
	float d=(a+b+c)/3.;
	if(a>b){
		t=a;
		a=b;
		b=t;
	}
	if(a>c){
		t=a;
		a=c;
		c=t;
	}
	if(b>c){
		t=b;
		b=c;
		c=t;
	}
	printf("in order:%d %d %d\n",a,b,c);
	printf("the average is:%f\n",d);
	return 0;	
}
