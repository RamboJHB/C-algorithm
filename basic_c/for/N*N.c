// N*N 乘法表

#include <stdio.h>

int main(){
	int i,j,k,N;
	scanf("%d",&N);

	for(i=1;i<=N;i++){	        // 控制行
		for(j=1;j<=i;j++){	// 控制列
			k=i*j;
			printf("%dx%d=%d ",j,i,k);
			if(k<10&&(j==2||j==3)){
				printf(" ");
			}	
		}		
		printf("\n");
	}
}
