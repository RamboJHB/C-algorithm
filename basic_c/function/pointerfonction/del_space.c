#include <stdio.h>
#include <string.h>

char* del(char *s);

int main(){
    char str[]="  how     r         u";

    puts(str);
    printf("%s\n",del(str));
    puts(str);
    return 0;
}

char* del(char* s){   //char  s=str
    char *r=s,*p=s;     //r为数组打起始地址 *r为第一个字符
    while (*s!='\0')
    {
        if(*s==' '){
            s++;            //s指针从头扫描到尾 到空格停下
        }
        else{
            *p=*s;          //不是空格的字符放前面
            s++;
            p++;
        }
    }
    *p='\0'; 
    return r;       //返回字符串起始地址
}
