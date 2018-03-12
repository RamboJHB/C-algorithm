//pan ding shi bu shi zhi shu
//
//
#include <string.h>
#include <stdio.h>

int main(){
	int a,i=2,flag=0;
	scanf("%d",&a);
	if(a==1){
		printf("not either\n");
	}
	if(a==2){
		printf("It is the smallest zhishu.\n");
	}
	if(a>2){
		while(i<a){
			if((a%i)==0){
				printf("It is not.\n");
				flag=1;
				break;
			}
			i++;
		}
		if(flag==0){
			printf("It is.\n");
		}
	}

}
