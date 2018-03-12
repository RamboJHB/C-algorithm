#include <stdio.h>
#include <errno.h>
#include <string.h>

struct student {
    long int number;
    char name[10];
    float score;
}group[]={{2103,"jiang",100},{2104,"jay",59.9}};

int main (int argc , char** argv){
    //get a string:buf
    FILE *fp;
    int s[10];
    if ((fread(s,sizeof(int),10,fp))<0){
        printf("fread error");
        return -1;
    }

    FILE *fp_;
    fwrite(group,sizeof(struct student),2,fp_);
    fclose(fp);
    fclose(fp_);
    return 0;
}
