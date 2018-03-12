#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	int x,i,num,n;
	char a[100];
	while(scanf("%s%d",a,&x)==2){//输入x为要转换的进制
        n=0;
		//如果x小于零，转换成正数再计算，然后先把负号输出
		
        //把arry中的string变成int数字
        //for(int i=0;i<strlen(a);i++)
        //a_=a+'0';
        //一下为转换成十进制的基本换规则
		for(i=0;i<strlen(a);i++){
			n=n*x+a[i]-'0';      
		} 
        //如果要转换的进制大于十进制，要特别处理。
		
        printf("\nvoila~ %s of %d is %d in decimal system\n ",a,x,n);             
	}
	return 0;
}

