//array  shuru shuchu
#include <string.h>
#include <stdio.h>

int main(){
	char a[10];
	int i,j,t;
	scanf("%s",a);		//%s zifuchuan
	puts(a);		//<string.h>
	printf("third is %c (a[2])\n",a[2]);	//%c ziyuan
	
	
	printf("in order:\n");
	for(i=0;i<10;i++)
		printf("a[%d] is %c\n",i,a[i]);
	printf("\n");	
	
	
	printf("in back order:\n");
	for(i=9;i>=0;i--)
		printf("%d %c \n",a[i],a[i]);
	printf("\n");
	
	return 0;
}

