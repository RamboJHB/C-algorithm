#include <stdio.h>
//#include <>

int main()
{
  float a=3.0;
  float* p=&a;
  printf("@ of a = %p, a = %f\n",&a,a);
  printf("p = %p, @ of p = %p, *p = %f\n",p,&p,*p);
  return 0;

}
