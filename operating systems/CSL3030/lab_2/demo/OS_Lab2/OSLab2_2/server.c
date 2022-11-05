#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

typedef struct message{
	long type;
	char text[256];
} message;

int main(){
    int k=3;
    printf("Enter number of clients : ");
    scanf("%d",&k);
    system("touch msgq.txt");
    key_t key;
    key = ftok("1@Ceyxasm",0);
    if(key==-1){
        printf("error1\n");
        perror("ftok");
        exit(1);
    }


    int msgq_id = msgget(key,0644 | IPC_CREAT);
    if(msgq_id==-1){
        printf("error2\n");
        perror("msgget");
        exit(1);
    }
    int mx=0;
    int winner[k];
    for(int i=0; i<k; i++) winner[i]=0;
    int i=0;
    while(mx<50){
        message msg;
        if(i==0){
            fgets(msg.text,256,stdin);
            i++;
            continue;
        }
        
        

        int min,max;
        printf("Question %d from server , Enter minimum and maximum value separated by space: ",i);
        scanf("%d",&min);
        scanf("%d",&max);
        msg.type=1;
        printf("\n");
        i++;

        int answer[k];
        for(int j=0; j<k; j++){
            answer[j]=0;
            printf("Enter answer from client %d \n: ",j+1);
            char buffer[256];
            char *num;
            asprintf(&num,"%d",min);
            strcat(strcpy(buffer,"./client "),num);
            asprintf(&num,"%d",max);
            strcat(buffer," ");
            strcat(buffer, num);
            asprintf(&num,"%d",j);
            strcat(buffer," ");
            strcat(buffer, num);
            system(buffer);
            message msg;
            msgrcv(msgq_id,&msg,256,2,0);
            int len = strlen(msg.text);
            answer[j] = atoi(msg.text);
        }
        int win=0;
        int guess=int(rand()%(max-min+1)+min);
        for(int j=0; j<k; j++){
            if(abs(answer[j]-guess)<abs(answer[win]-guess)) win=j;
        }
        winner[win]+=5;
        if(winner[win]>mx) mx=winner[win];

        printf("Question : %d %d\n",min,max);
        for(int j=0; j<k; j++){
            printf("Client : %d, Guess: %d,Score : %d\n",j+1,answer[j],winner[j]);
        }
        printf("Round Winner: Client %d\n",win+1);
        printf("\n");
    }

    
    int win=0;
    for(int i=0; i<k; i++){
        if(winner[i]>winner[win]) win=i;
    }
    printf("Winner is : client %d\n",win+1);
    return 0;
}
