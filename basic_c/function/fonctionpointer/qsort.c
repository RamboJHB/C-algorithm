#include <stdio.h>
#include <stdlib.h>

int compare_int(const void *p,const void *q);

int main(){
    int a[]={51,4,321,22,2,4};
    int n= sizeof(a)/sizeof(int);
    
    qsort(a,n,sizeof(int),compare_int);
    
    for(int i=0;i<n;i++)
        printf("%d\n",a[i]);
    return 0;
}

int compare_int(const void *p,const void *q){
    return (*(int*)p-*(int*)q);
}
