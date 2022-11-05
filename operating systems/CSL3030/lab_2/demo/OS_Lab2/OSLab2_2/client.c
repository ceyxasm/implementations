#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <time.h>

typedef struct message{
	long type;
	char text[256];
} message;

int main(int argc, char* argv[]){
srand(time(0)*atoi(argv[3]));
    int min = atoi(argv[1]);
    int max = atoi(argv[2]);
    key_t key;
    key = ftok("msgq.txt",0);
    if(key==-1){
        perror("ftok");
        exit(1);
    }
    int msgq_id = msgget(key,0644);
    if(msgq_id==-1){
        perror("msgget");
        exit(1);
    }
    message msg;
    int n=256;

    message answer;
    char* num;
    
    asprintf(&num,"%d",int(rand()%(max-min+1)+min));
    strcpy(answer.text,num);
    answer.type=2;
    if(msgsnd(msgq_id, &answer, 256,0)==-1){
        perror("msgsnd");
        exit(1);
    }
    else{
        exit(1);
    }

    return 0;
}
