#include <stdio.h>

int plus(int a,int b){return (a+b);}
int minus(int a,int b){return (a-b);}
double division(int a ,int b){return (a/b);}

int main(){
    int m,n;

    int (*p[2])(int,int);
    
    while(scanf("%d%d",&m,&n)){
//        printf("%d\n",plus(m,n));
  //      printf("%d\n",minus(m,n));
        
        p[0]=plus;
        printf("%d\n",(*p)(m,n));
        p[1]=minus;
        printf("%d\n",(*p[1])(m,n));
    }
    return 0;
}
