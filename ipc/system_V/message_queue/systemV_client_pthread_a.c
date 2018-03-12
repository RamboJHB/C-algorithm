//Client–server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>

typedef struct{
    long mtype;             //message type
    char mtext[64];
}MSGQ;

#define LEN (sizeof(MSGQ)-sizeof(long))  //message size with out type
#define TypeA 100
#define TypeB 200

void *A(void *arg){
    while (1){
        buf.mtype=TypeA;
        printf("input:\n");
        fgets(buf.mtext,64,stdin);                  //1.input
        msgsnd(msgid,&buf,LEN,0);                   //2.send

        if (strcmp(buf.mtext,"quit\n")==0){
            break;
        }
        if (msgrcv(msgid,&buf,LEN,TypeB,0)<0){      //3.recv
            perror("msgrcv");
            exit(-1);
        }
        printf("recv from B : %s",buf.mtext);       //3.print
        if (strcmp(buf.mtext,"quit\n")==0){
            msgctl(msgid,IPC_RMID,0);
            exit(0);
        }
    }
}

int main(int argc,char** argv){

    MSGQ buf;           //buf is MSGQ type variable
    buf.mtype=100;      //id of message q

    //get a key
    key_t key;
    int msgid;          //message id
    if ((key=ftok(".",'q'))==-1){
        perror("ftok");
        exit(-1);
    }
    //make a message queue
    if((msgid=msgget(key,IPC_CREAT|0666))<0){
        perror("msgget");
        exit(-1);
    }
    return 0;
}
