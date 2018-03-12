//yong * hua lingxing

#include <stdio.h>

int main(){
	int i,j,k,N;
    while((printf("enter a number: ")&&scanf("%d",&N))==1){

	    for(i=0;i<=N-1;i++){	        // 控制行
		    for(j=0;j<=N-i-2;j++)	// 控制空格
			    printf(" ");
		    for(k=0;k<=2*i;k++)     // 控制星号
			    printf("*");
		    printf("\n");
	    }

	    for(i=0;i<=N-1;i++){		//hang
		    for(j=0;j<=i;j++)	//kongge
			    printf(" ");
		    for(k=0;k<=2*(N-i-2);k++)//xinghao
			    printf("*");
		    printf("\n");
	    }
    }
}
