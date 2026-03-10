# include <stdio.h>
struct Process{
    int pid;
    int at;
    int bt;
};
int main(){
    int n;
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    struct Process queue[n];
    printf("Enter the pid,arrival time,burst time for each process.\n");
    for(int i=0;i<n;i++){
        scanf("%d%d%d",&queue[i].pid,&queue[i].at,&queue[i].bt);
    }
    for(int i=0;i<n-1;i++){
        for(int j=1;j<n;j++){
            if(queue[j].at<queue[j-1].at){
                struct Process temp=queue[j];

                queue[j]=queue[j-1];
                queue[j-1]=temp;
            }else if(queue[j].at==queue[j-1].at && queue[j].pid<queue[j-1].pid){
                struct Process temp=queue[j];
                queue[j]=queue[j-1];
                queue[j-1]=temp;
            }
        }
    }
    int ct[n],tat[n],wt[n];
    ct[0]=queue[0].at+queue[0].bt;
    for(int i=1;i<n;i++){
        if(queue[i].at>ct[i-1]){
            ct[i]=queue[i].at+queue[i].bt;
        }else{
            ct[i]=ct[i-1]+queue[i].bt;
        }
    }
    for(int i=0;i<n;i++){
        tat[i]=ct[i]-queue[i].at;
        wt[i]=tat[i]-queue[i].bt;
    }
    printf("\nProcess_ID | Arrival Time | Burst Time | Completion Time | TurnAround Time | Waiting Time   \n");
    for(int i=0;i<n;i++){
        printf("%10d%15d%13d%18d%18d%15d\n",queue[i].pid,queue[i].at,queue[i].bt,ct[i],tat[i],wt[i]);
    }
}
