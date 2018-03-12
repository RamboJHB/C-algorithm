#include <stdio.h>

int factorial(int);

int main(){
    int n;
    
    while(scanf("%d",&n)==1){
        printf("n!=%d\n",factorial(n));
    }
    return 0;
}

int factorial(int a){
    if (a==0||a==1)
        return 1;
//    printf("%d \n",a);
    return (a*factorial(a-1));
    
}
