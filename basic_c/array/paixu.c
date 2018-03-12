//array   排顺序

#include <stdio.h>

int main(){
	int a[10],i,j,t;

	for(i=0;i<10;i++){
		scanf("%d",&a[i]);
	}
	printf("in back order:");
	for(i=9;i>=0;i--)
		printf("%d ",a[i]);
	printf("\n");
	
	for(i=0;i<10;i++){
		for(j=i+1;j<10;j++){
			if(a[i]>a[j]){
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}
	printf("smaill to big:");
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");
	printf("big to small:");
	for(i=9;i>=0;i--)
		printf("%d ",a[i]);
	printf("\n");	
				
	return 0;
}
