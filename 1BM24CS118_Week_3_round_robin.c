#include <stdio.h>

#define MAX 10

typedef struct {
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
} Process;

Process p[MAX];
int n;

void round_robin(int quantum) {
    int time = 0, completed = 0;
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};

    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
    }

    printf("\n--- Round Robin Scheduling ---\n");

    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {
        if (front == rear) {
            time++;
            for (int i = 0; i < n; i++) {
                if (p[i].arrival <= time && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int i = queue[front++];

        if (p[i].remaining > 0) {
            int exec = (p[i].remaining > quantum) ? quantum : p[i].remaining;

            for (int t = 0; t < exec; t++) {
                printf("Time %d -> Process %d\n", time, p[i].id);
                time++;

                for (int j = 0; j < n; j++) {
                    if (p[j].arrival <= time && !visited[j]) {
                        queue[rear++] = j;
                        visited[j] = 1;
                    }
                }
            }

            p[i].remaining -= exec;

            if (p[i].remaining == 0) {
                p[i].completion = time;
                p[i].turnaround = p[i].completion - p[i].arrival;
                p[i].waiting = p[i].turnaround - p[i].burst;
                completed++;
            } else {
                queue[rear++] = i;
            }
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].arrival,
               p[i].burst,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);
    }
}

int main() {
    int quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &quantum);

    round_robin(quantum);

    return 0;
}
