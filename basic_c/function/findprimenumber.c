//

#include <stdio.h>
#include <string.h>

int P(int);

void main(){
	int a,i=0;
	while(i=10){
		scanf("%d",&a);
			if(P(a)){
				printf("Y\n");
			}else{
				printf("N\n");
			}
	//	i++;
	}
}

int P(int n){
	int i,p=1;	
	if(n<2){
		return 0;
	}else{
		for(i=2;i<n;i++){
			if((n%i)==0){
				p=0;
				return p;
			}
		}
	}
}
