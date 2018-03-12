#include <stdio.h>
#include <errno.h>
#include <string.h>

#define N 6

int main (int argc , char** argv){
    //get a string:buf
    char buf[N];
    fgets(buf,N,stdin);
    printf("%s\n",buf);      //char* buf// printf %s buf
    

    //count how many lines in a text
    //with fgetc           //this is slow
    
    FILE *fp;
    int ch,count=0;
    if ((fp=fopen(argv[1],"r"))==NULL){
        perror("fopen error");
        return -1;
    }else {
        while ((ch=fgetc(fp))!=EOF){
            if(ch=='\n')
                count++;
        }
    }
    printf("fgetc total %d lines\n",count);
    
    //count how many lines in a text
    //with fgets         
    
    FILE *fp_;
    count=0;
    if ((fp_=fopen(argv[1],"r"))==NULL){
        perror("fopen error");
        return -1;
    }else {
        while( fgets(buf,6,fp_)!=NULL)
            if(buf[strlen(buf)-1]=='\n')
                count++;
    }

    printf("fgets total %d lines\n",count);
    
    fclose(fp);
    fclose(fp_);
    return 0;
}
