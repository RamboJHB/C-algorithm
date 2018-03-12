//sercet code translation  
//begin with + A become C
//- E to C
//+ Z to B

#include <string.h>
#include <stdio.h>

int main(){
	char a[100],b[100];
	int i;
//	gets(a);	//dangerous to use?
	scanf("%s",&a);
	if(a[0]=='+'){
		for(i=1;i<strlen(a);i++){
			a[i]=a[i]+2;		//a[i]+=2 A to C
			if(((a[i]>'Z')&&(a[i]<'a'))||(a[i]>'z')){
				a[i]-=26;	//
			}
		}
	}
	if(a[0]=='-'){
		for(i=1;i<strlen(a);i++){
			a[i]-=2;		//C to A
			if((a[i]<'A')||((a[i]>'Z')&&(a[i]<'a'))){
				a[i]+=26;	//
			}
		}
	}
	puts(a+1);		//+1 to delete 1st element"+"/"-"
	printf("%s\n",a+1);
	return 0;

}
