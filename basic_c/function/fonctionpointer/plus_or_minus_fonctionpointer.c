#include <stdio.h>

int plus(int a,int b){return (a+b);}
int minus(int a,int b){return (a-b);}

int main(){
    int m,n;

    int (*p)(int,int);
    
    while(scanf("%d%d",&m,&n)){
//        printf("%d\n",plus(m,n));
  //      printf("%d\n",minus(m,n));
        
        p=plus;
        printf("%d\n",(*p)(m,n));
        p=minus;
        printf("%d\n",(*p)(m,n));
    }
    return 0;
}
