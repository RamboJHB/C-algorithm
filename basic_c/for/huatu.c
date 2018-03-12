//文字画图

#include <stdio.h>

int main(){
	int a,i;

	printf("count to:");
	scanf("%d",&a);

	for(i=1;i<=a;i++){             //次数
		printf("*");
	}
	printf("\n");
	return 0;	
}
