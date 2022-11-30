#include<stdio.h>
#include <stdlib.h>
#include <math.h>

int diskStartIndex = 0;
int cylinderRequests[1000];
int totalCylinders;

void printArr(int *arr)
{
    for(int i=0;i<totalCylinders;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

void fcfs_DiskScheduling()
{
    int waitingTime[1000],seq[1000];
    int avgWaitingTime,totalCylMovement,currWait;
    int start = cylinderRequests[1];
    cylinderRequests[0] = start;
    int wait=0;

    for(int i=0;i<=totalCylinders-1;i++)
    {
        currWait=abs(cylinderRequests[i+1]-cylinderRequests[i]);
        wait+=currWait;
        seq[i]=cylinderRequests[i+1];
        waitingTime[i]=currWait;
    }
    printf("\n");

    printf("Sequence of requsets : ");
    printArr(seq);

    printf("Waiting time for every request : ");
    printArr(waitingTime);

    printf("Avg waiting time : %f \n",wait/(float)totalCylinders);
    printf("TurnAround for every request : ");
    int turnAround=0;
    for(int i=1;i<=totalCylinders;i++){
        printf("%d ",waitingTime[i]);
        turnAround = turnAround + waitingTime[i];
    }
    printf("\nAverage TurnAround time : %f",turnAround/(float)totalCylinders);
    printf("\n");
    printf("Total Cylinder Movement : %d \n",wait);
    printf("____________________________________________________\n\n\n");

}

void scan_DiskScheduling(){

    int queue[25],n=totalCylinders,start,i,j,k,seek=0, maxrange=199,
    d,temp,arr_fir[20],arr_sec[20],flag1=0,flag2=0;
    float averageSeekTime;

    int waitingTime[1000],seq[1000];
    int avgWaitingTime,totalCylMovement,currWait;

    start = cylinderRequests[1];
    for(i=1;i<=n;i++)   
    {
        temp=cylinderRequests[i];  
        if(temp>start)
        {
            arr_fir[flag1]=temp; 
            flag1++;
        }
        else  
        {   
            arr_sec[flag2]=temp; 
            flag2++;
        }
    }
    for(i=0;i<flag1-1;i++)
    {
        for(j=i+1;j<flag1;j++)
        {
            if(arr_fir[i]>arr_fir[j])
            {
                temp=arr_fir[i];
                arr_fir[i]=arr_fir[j];
                arr_fir[j]=temp;
            }
        }
    }
    
    for(i=0;i<flag2-1;i++)
    {
        for(j=i+1;j<flag2;j++)
        {
            if(arr_sec[i]<arr_sec[j])
            {
                temp=arr_sec[i];
                arr_sec[i]=arr_sec[j];
                arr_sec[j]=temp;
            }
        }
    }    
    
    for(i=1,j=0;j<flag1;i++,j++)
    {
        queue[i]=arr_fir[j]; 
    }
    queue[i]=maxrange;
    for(i=flag1+2,j=0;j<flag2;i++,j++)
    {
        queue[i]=arr_sec[j];
    }
    

    queue[i]=0;

    queue[0]=start;
    printArr(queue);
    for(j=0; j<=n; j++)
    {   
        d = abs(queue[j+1]-queue[j]);
        // printf("%d \n",d);

        seek = seek + d;
        seq[j]=queue[j];
        waitingTime[j]=d;
    }
    
    averageSeekTime = seek/(float)n;
    printf("\n");
    printf("Sequence of requests : ");
    printArr(seq);

    printf("Waiting time for every request : ");
    printArr(waitingTime);
    
    printf("Average waiting Time : %f ms\n", averageSeekTime);
    printf("TurnAround for every request : ");
    int turnAround=0;
    for(int i=1;i<=totalCylinders;i++){
        printf("%d ",waitingTime[i]);
        turnAround = turnAround + waitingTime[i];
    }

    printf("\n Average TurnAround time : %f",turnAround/(float)totalCylinders);
    printf("\n");

    printf("Total Cylinder Movements: %d\n", seek);
    printf("____________________________________________________\n\n\n");
}


void c_scanDiskScheduling(){

    int queue[20],n,start,i,j,k,seek=0,max=199,diff,temp,arr_fir[20],arr_sec[20],
    flag1=0,flag2=0;  

    int waitingTime[1000],seq[1000];
    int avgWaitingTime,totalCylMovement,currWait;

    float avg;
    n=totalCylinders;
    start = cylinderRequests[1];
    for(i=1;i<=n;i++)
    {
        temp=cylinderRequests[i];
        if(temp>=start)
        {
            arr_fir[flag1]=temp;
            flag1++;
        }
        else
        {
            arr_sec[flag2]=temp;
            flag2++;
        }
    }

    for(i=0;i<flag1-1;i++)
    {
        for(j=i+1;j<flag1;j++)
        {
            if(arr_fir[i]>arr_fir[j])
            {
                temp=arr_fir[i];
                arr_fir[i]=arr_fir[j];
                arr_fir[j]=temp;
            }
        }
    }
    for(i=0;i<flag2-1;i++)
    {
        for(j=i+1;j<flag2;j++)
        {
            if(arr_sec[i]>arr_sec[j])
            {
                temp=arr_sec[i];
                arr_sec[i]=arr_sec[j];
                arr_sec[j]=temp;
            }
        }
    }

    for(i=1,j=0;j<flag1;i++,j++)queue[i]=arr_fir[j];

    queue[i]=max;
    queue[i+1]=0;
    for(i=flag1+3,j=0;j<flag2;i++,j++)
    queue[i]=arr_sec[j];
    queue[0]=start;

    for(j=0;j<=n+1;j++)
    {
        diff=abs(queue[j+1]-queue[j]);
        seek+=diff;

        seq[j]=queue[j];
        waitingTime[j]=diff;
    }

    printf("\n");

    printf("Sequence of requets : ");


    for(int k=0;k<=n+1;k++){
        printf("%d ",seq[k]);
    }
    printf("\n");
    printf("Waiting time for every request : ");

    for(int k=0;k<=n+1;k++)
        printf("%d ",waitingTime[k]);
    printf("\n");

    avg=seek/(float)n;
    printf("Average waiting time is %f ms\n",avg);
    int turnAround=0;
    printf("TurnAround for every request : ");

    for(int i=1;i<=totalCylinders;i++){
        printf("%d ",waitingTime[i]);
        turnAround = turnAround + waitingTime[i];
    }

    printf("\n Average TurnAround time : %f",turnAround/(float)totalCylinders);
    printf("\n");

    printf("Total Cylinder movement is %d\n",seek);
    printf("____________________________________________________\n\n\n");
            
}

void sstf_DiskScheduling(){

    int queue[100], arr_sec[100], q_size=totalCylinders, start, seek=0, temp;
    float avg;

    int waitingTime[1000],seq[1000];
    int avgWaitingTime,totalCylMovement,currWait;

    for(int i=1; i<=q_size; i++)
        queue[i-1]=cylinderRequests[i];
    

    start = queue[0];
    for(int i=0; i<q_size; i++){
        arr_sec[i] = abs(start-queue[i]);
    }


    for(int i=0; i<q_size; i++){
        for(int j=i+1; j<q_size;j++)
        {
            if(arr_sec[i]>arr_sec[j]){
                temp = arr_sec[i];
                arr_sec[i]=queue[j];
                arr_sec[j]=temp;

                temp=queue[i];
                queue[i]=queue[j];
                queue[j]=temp;
            }
        }
    }
    waitingTime[0]=0;

    for(int i=1; i<q_size; i++)
    {
        waitingTime[i]= abs(start-queue[i]);
        seek = seek+abs(start-queue[i]);
        start = queue[i];
    }

    printf("\nSequence of requests : ");
    printArr(queue);

    printf("Waiting time for processes : ");
    printArr(waitingTime);

    avg = seek/(float)q_size;
    printf("Average seek time is %f\n", avg);

    printf("TurnAround for every request : ");
    int turnAround=0;

    for(int i=1;i<=totalCylinders;i++){
        printf("%d ",waitingTime[i]);
        turnAround = turnAround + waitingTime[i];
    }

    printf("\n Average TurnAround time : %f",turnAround/(float)totalCylinders);
    printf("\n");

    printf("Total Cylinder Movements %d\n",seek);
    printf("____________________________________________________\n\n\n");
}




int main()
{
    int requests;
    printf("Enter total number of cylinders : ");
    scanf("%d",&totalCylinders);
    cylinderRequests[0]=-1;
    printf("enter number of requestes : ");
    scanf("%d",&requests);
    printf("Enter request arrival time for requests : ");
    for(int i=1;i<=requests;i++) scanf("%d",&cylinderRequests[i]);

    printf("\n\n");
    while(1)
    {
        printf("Enter \n1 for FCFS \n2 for SCAN\n3 for C_SCAN\n4 for SSTF\nany other to exit\n");
        int inp;
        scanf("%d",&inp);
        if(inp==1){
            fcfs_DiskScheduling();
            printf("\n");
        }  else if(inp==2){
            scan_DiskScheduling();
            printf("\n");
        }    else if(inp==3){
            c_scanDiskScheduling();
            printf("\n");
        }  else if(inp==4){
            sstf_DiskScheduling();
            printf("\n");
        } else {
            break;
        }

    }
    return 0;

}


