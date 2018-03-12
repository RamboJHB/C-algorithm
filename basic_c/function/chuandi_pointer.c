#include <stdio.h>

void swap(int*,int*);

int main(){
    int n=3, m=6;
    
    printf("before fonction n=%d m=%d\n",n,m);
    swap(&m,&n);
    printf("after  fonction n=%d m=%d\n",n,m);
    
    return 0;
}

void swap(int* q,int* p){  //int *q=&n, *p=&m
    int* t;
    t=p;
    p=q;
    q=t;
}
