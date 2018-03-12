//zhao zhi shu


#include <string.h>
#include <stdio.h>

int main(){
	int a,b,i,n,flag;

	printf("count from:");
	scanf("%d",&a);
	printf("to:");
	scanf("%d",&b);
	if(a>b){
		int t=b;
		b=a;
		a=t;	
	}

	printf("From %d to %d zhishu you: ",a,b);
	if(a<=2){
		printf("2 ");
	}

	for(i=a;i<=b;i++){
		for(n=2;n<i;n++){
			flag=0;
			if((i%n)==0){
				flag=1;
				break;
			}
		}
		if(!flag){
			printf("%d ",i);
		}
	}


	printf("\n");
	return 0;
}
