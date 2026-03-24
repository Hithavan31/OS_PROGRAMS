# include <stdio.h>
struct Process{
int pid;
int at;
int bt;
int priority;
int ct,tat,wt;
};
int main(){
int n;
printf("Enter the number of processes\n");
scanf("%d",&n);
struct Process q[n];
printf("Enter the pid,priority,arrival time,burst time for each process.\n");
int done[n];
for(int i=0;i<n;i++){
scanf("%d%d%d%d",&q[i].pid,&q[i].priority,&q[i].at,&q[i].bt);
done[i]=0;
}
int completed=0,current_time=0;
while(completed!=n){
int minIndex=-1,minPriority=9999;
for(int i=0;i<n;i++){
if(q[i].at<=current_time && done[i]==0){
if(q[i].priority < minPriority){
minPriority=q[i].priority;
minIndex=i;
}
if(q[i].priority == minPriority){
if(q[i].at < q[minIndex].at){
minIndex=i;
}
}
}
}
if(minIndex==-1){
current_time++;
}else{
completed++;
current_time+=q[minIndex].bt;
q[minIndex].ct=current_time;
q[minIndex].tat=q[minIndex].ct-q[minIndex].at;
q[minIndex].wt=q[minIndex].tat-q[minIndex].bt;
done[minIndex]=1;
}
}

printf("\nPriority | Process_ID | Arrival Time | Burst Time | Completion Time | TurnAround Time | Waiting Time \n");
for(int i=0;i<n;i++){
printf("%8d%13d%15d%13d%18d%18d%15d\n",q[i].priority,q[i].pid,q[i].at,q[i].bt,q[i].ct,q[i].tat,q[i].wt);
}
float avg_tat=0,avg_wt=0;
for(int i=0;i<n;i++){
avg_tat+=q[i].tat;
avg_wt+=q [i].wt;
}
printf("Average TAT = %.2f, Average WT = %.2f\n",avg_tat/n,avg_wt/n);
}
