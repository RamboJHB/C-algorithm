#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h> //sleep
#include <time.h>   //time_t time(time_t *t),localtime()


int main (int argc , char** argv){

    FILE *fp;
    char buf[64]={0};
    int line=0;
    time_t t;
    struct tm *tp;

    //open a stream 
    if ((fp=fopen("time.txt","a+"))==NULL){   
        perror("fopen time.txt error");
        return -1;
    }

    //how many line existed //go to the end of file
    while (fgets(buf,64,fp)!=0)
    {   
        if (buf[strlen(buf)-1]=='\n')   //got a line in buf
            line++;   
    }                                   //position is end of time.txt
    
    
    while (1)       //do this all along
    {   
        time(&t);
        tp=localtime(&t);
        fprintf(fp,"%02d. %d-%02d-%02d %02d:%02d:%02d\n",line++,tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday,tp->tm_hour,tp->tm_min,tp->tm_sec);
        printf("%02d. %d-%02d-%02d %02d:%02d:%02d\n",line,tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday,tp->tm_hour,tp->tm_min,tp->tm_sec);
        fflush(fp); 
        sleep(3);
    }
    
    fclose(fp);
    return 0;
}
