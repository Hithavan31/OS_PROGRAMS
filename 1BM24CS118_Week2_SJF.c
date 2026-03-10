# include <stdio.h>
struct Process{
    int pid;
    int at;
    int bt;
    int ct,tat,wt;
};
int main(){
    int n;
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    struct Process queue[n];
    printf("Enter the pid,arrival time,burst time for each process.\n");
    int done[n];
    for(int i=0;i<n;i++){
        scanf("%d%d%d",&queue[i].pid,&queue[i].at,&queue[i].bt);
        done[i]=0;
    }
    int completed=0,current_time=0;
    while(completed!=n){
        int minIndex=-1,minTime=9999;
        for(int i=0;i<n;i++){
            if(queue[i].at<=current_time && done[i]==0){
                if(queue[i].bt < minTime){
                    minTime=queue[i].bt;
                    minIndex=i;
                }
                if(queue[i].bt == minTime){
                    if(queue[i].at < queue[minIndex].at){
                        minIndex=i;
                    }
                }
            }
        }
        if(minIndex==-1){
            current_time++;
        }else{
            completed++;
            current_time+=queue[minIndex].bt;
            queue[minIndex].ct=current_time;
            queue[minIndex].tat=queue[minIndex].ct-queue[minIndex].at;
            queue[minIndex].wt=queue[minIndex].tat-queue[minIndex].bt;
            done[minIndex]=1;
        }
    }

    printf("\nProcess_ID | Arrival Time | Burst Time | Completion Time | TurnAround Time | Waiting Time   \n");
    for(int i=0;i<n;i++){
        printf("%10d%15d%13d%18d%18d%15d\n",queue[i].pid,queue[i].at,queue[i].bt,queue[i].ct,queue[i].tat,queue[i].wt);
    }
    float avg_tat=0,avg_wt=0;
    for(int i=0;i<n;i++){
        avg_tat+=queue[i].tat;
        avg_wt+=queue[i].wt;
    }
    printf("Average TAT = %.2f, Average WT = %.2f\n",avg_tat/n,avg_wt/n);
}
