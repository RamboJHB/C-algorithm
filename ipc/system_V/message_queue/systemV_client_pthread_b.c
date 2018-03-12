#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>

typedef struct{
    long mtype;        
    char mtext[64];
}MSGQ;

#define LEN (sizeof(MSGQ)-sizeof(long))  
#define TypeA 100
#define TypeB 200

int main(int argc,char** argv){
    MSGQ buf;          
    buf.mtype=100;     
    key_t key;
    int msgid;       
    if ((key=ftok(".",'q'))==-1){
        perror("ftok");
        exit(-1);
    }
    if((msgid=msgget(key,IPC_CREAT|0666))<0){
        perror("msgget");
        exit(-1);
    }

    while (1){
        if (msgrcv(msgid,&buf,LEN,TypeA,0)<0){      //1.recv
            perror("msgrcv");
            exit(-1);
        }
        if (strcmp(buf.mtext,"quit\n")==0){         
            msgctl(msgid,IPC_RMID,0);
            exit(0);
        }
     
        printf("recv from A : %s",buf.mtext);       //2.print
        buf.mtype=TypeB;
        printf("input:\n");
        fgets(buf.mtext,64,stdin);                  //3.input
        msgsnd(msgid,&buf,LEN,0);                   //4.send
        if (strcmp(buf.mtext,"quit\n")==0){
            break;
        }
    }
    return 0;
}
