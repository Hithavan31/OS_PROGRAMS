#include <stdio.h>

struct Process {
    int pid;
    int capacity;
    int period;
    int remCapacity;
};

int gcd(int a,int b){
    while(b){
        a%=b;
        int t=a;
        a=b;
        b=t;
    }
    return a;
}

int findLcm(int a,int b){
    if(a==0||b==0)return 0;
    return (a*b)/gcd(a,b);
}

int main(){
    int n;
    printf("Enter the number of processes.\n");
    scanf("%d",&n);
    struct Process p[n];
    int lcm=1;

    printf("Enter the pid, capacity, period of each process.\n");
    for(int i=0;i<n;i++){
        scanf("%d%d%d",&p[i].pid,&p[i].capacity,&p[i].period);
        p[i].remCapacity=0;
        lcm=findLcm(lcm,p[i].period);
    }

    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(p[j].period<p[j-1].period){
                struct Process temp=p[j];
                p[j]=p[i];
                p[i]=temp;
            }
        }
    }

    printf("\nLCM: %d\n",lcm);
    printf("Time | Process\n");
    for(int t=0;t<lcm;t++){
        for(int i=0;i<n;i++){
            if(t%p[i].period==0){
                p[i].remCapacity=p[i].capacity;
            }
        }

        int selected=-1;
        for(int i=0;i<n;i++){
            if(p[i].remCapacity>0){
                selected=i;
                break;
            }
        }

        printf("%d | ",t);
        if(selected!=-1){
            printf("P%d\n",p[selected].pid);
            p[selected].remCapacity--;
        }else{
            printf("IDLE\n");
        }
    }

    return 0;
}
