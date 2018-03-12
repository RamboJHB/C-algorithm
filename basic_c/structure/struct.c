#include <stdio.h>

struct student {
    int group;
    char name[9];
    struct {
        int month;
        int date;
    }birthday;
    float score;
}group1[1];

void print_info(struct student *a,int n);

int main (int argc , char** argv){
    int i;

    //initialization
    struct student group2[]={{2,"jiang",{1,21},99.9},{2,"jay",{12,31},59}};
     
    printf("group\tname\tbirthday score\n");
    
    //fuzhi
    struct student best=group2[0];
    printf("%d\t%s\t%d.%d\t%f print best whit best.\n",best.group,best.name,best.birthday.month,best.birthday.date,best.score);
    
  
    group1[0]=group2[0];group1[1]=group2[1]; //    group1[]=group2[]; & group1=group2; error
    group1[0].group=1;group1[1].group=1;
    for (i=0;i<=sizeof(group1)/sizeof(struct student);i++){
        printf("%d\t%s\t%d.%d\t%f print group1\n",group1[i].group,group1[i].name,group1[i].birthday.month,group1[i].birthday.date,group1[i].score);
    }
    
    //print group 1 with pointer
    struct student * p=group1;      // p=&group1[0]; the same
    for (i=0;i<=sizeof(group1)/sizeof(struct student);i++){
        printf("%d\t%s\t%d.%d\t%f print group1 with pointer p[i]. \n",p[i].group,p[i].name,p[i].birthday.month,p[i].birthday.date,p[i].score);
    }
    for (i=0;i<=sizeof(group1)/sizeof(struct student);i++){
        printf("%d\t%s\t%d.%d\t%f print group1 with pointer (p+i)->\n",(p+i)->group,(p+i)->name,(p+i)->birthday.month,(p+i)->birthday.date,(p+i)->score);
    }
    print_info(group2,sizeof(group2)/sizeof(struct student) );

    return 0;
}

void print_info(struct student *a,int n){   //struct student *a=group2;
    int i;
    for(i=0;i<n;i++){
        printf("%d\t%s\t%d.%d\t%f print group2 with pointer p-> (*p). p++\n",(*a).group,a->name,a->birthday.month,a->birthday.date,a->score);
        a++;
    }
}
