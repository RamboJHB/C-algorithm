#include <stdio.h>
#include "x_de_n_cifang.h"

//double P(double,int);
int y=0;

int main(){
    int n=3;
    double x=3;
    
    y=111;
    printf("before fonction y=%d\n",y);
    
    printf("%lf\n",P(x,n));

//    y=333;
    printf("after fonction y=%d\n",y);
    return 0;
}

double P(double m,int n){  //double m=x, int n=n
    int r=1;
    for(int i=1;i<=n;i++)
        r*=m;            //x de n cifang = x*x*x*...*x
                         //r*=x <=> r=x*r
    y=222;
    printf("in fonction y=%d\n",y);
    return x;
}
