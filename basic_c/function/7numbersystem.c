//shuru 7jinzhi shu ran hou qiu he yong 7jin zhu biaoshi

#include <string.h>
#include <stdio.h>
#include <math.h>



int main(){
	char s1[10],s2[10];
	int a,b;
	scanf("%s%s",s1,s2);	//lu ru ziyuan 
	a=R7(s1);
	b=R7(s2);
	printf("%d+%d=%d",a,b,a+b);
	P7(a+b);
	return 0;
}

int R7(char s[]){
	int n,i,j;
	int len=strlen(s);
	for(i=0;i<len;i++){
		j=(s[i]-'0')*pow(7,len);

	}


	return n;
}

int P(){
	
	
	return ;
}
int exchange(int a)
{
    if(a == 10){printf("A");return 0;}
    if(a == 11){printf("B");return 0;}
    if(a == 12){printf("C");return 0;}
    if(a == 13){printf("D");return 0;}
    if(a == 14){printf("E");return 0;}
    if(a == 15){printf("F");return 0;}
    printf("%d",a);
}
int main(int argc, char *argv[])
{
    int x,y,i,j,a[100];
    while(scanf("%d%d",&x,&y) == 2)//输入x，y，x为十进制数，y为要转换的进制
    {
       if(x < 0){printf("-"); x = -x;}//如果x小于零，转换成正数再计算，然后先把负号输出
       if(x == 0){printf("0");return 0;}
       for(i = 0;x != 0;i++)//一下为十进制转换成其他进制的基本规则
          {
               a[i] = x % y;
             x = x / y;      
            } 
       i--;         
          if(y > 10)//如果要转换的进制大于十进制，要特别处理。
           for(j = i;j >= 0;j--)
              exchange(a[j]);  
       else for(j = i;j >= 0;j--)
               printf("%d",a[j]);
        printf("\n");             
    }
    return 0;
}
