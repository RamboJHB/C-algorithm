#include <stdio.h>

int exchange();

int main(int argc, char *argv[]){
	int x,y,i,j,a[100];
	while(scanf("%d%d",&x,&y)==2){//输入x，y，x为十进制数，y为要转换的进制

		printf("here it is: ");
		//如果x小于零，转换成正数再计算，然后先把负号输出
		if(x<0){printf("-");x=-x;}
		if(x==0){printf("0");return 0;}
		
		//一下为十进制转换成其他进制的基本规则
		for(i=0;x!=0;i++){
			a[i]=x%y;
			x=x/y;      
		} 
		i--;         
		//如果要转换的进制大于十进制，要特别处理。
		if(y >10)
			for(j=i;j>=0;j--)
				exchange(a[j]);  
		else for(j=i;j>=0;j--)
			printf("%d",a[j]);
		printf(" voila~ ");             
	}
	return 0;
}
int exchange(int a){
	if(a==10){printf("A");return 0;}
	if(a==11){printf("B");return 0;}
	if(a==12){printf("C");return 0;}
	if(a==13){printf("D");return 0;}
	if(a==14){printf("E");return 0;}
	if(a==15){printf("F");return 0;}
	printf("%d",a);
}
