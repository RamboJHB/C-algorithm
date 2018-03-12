#include <string.h>
#include <stdio.h>

int main(){
	//store and print a word into a array
	char a[100]="dfze";
	puts(a);
	printf("%s\n--------------------\n",a);

	//ziyuan
	char b='q';
	printf("ziyuan\tshuzi\n%c\t%d\n--------------------\n",b,b);

	//print a list of ASCII code 'A'-'a'=32
	char c;
	printf("\n-A list of ASCII code 'A' to 'z'------\n");
	printf("\"baifenhaoc\"\t\"baifenhaod\"\n");
	for(c='A';c<=96;c+=1){
		printf("%c\t%d\t\t%c\t%d\n",c,c,c+32,c+32);
	}

	return 0;
}
