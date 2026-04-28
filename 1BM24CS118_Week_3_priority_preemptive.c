#include <stdio.h>

#define MAX 10

typedef struct {
    int id;
    int arrival;
    int burst;
    int priority;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
} Process;

Process p[MAX];
int n;

void preemptive_priority() {
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
    }

    printf("\n--- Preemptive Priority Scheduling ---\n");

    while (completed < n) {
        int selected = -1;
        int best_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (p[i].priority < best_priority) {
                    best_priority = p[i].priority;
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            printf("Time %d -> Process %d\n", time, p[selected].id);
            p[selected].remaining--;

            if (p[selected].remaining == 0) {
                p[selected].completion = time + 1;
                p[selected].turnaround =
                    p[selected].completion - p[selected].arrival;
                p[selected].waiting =
                    p[selected].turnaround - p[selected].burst;
                completed++;
            }
        } else {
            printf("Time %d -> Idle\n", time);
        }

        time++;
    }

    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].arrival,
               p[i].burst,
               p[i].priority,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Priority (lower = higher priority): ");
        scanf("%d", &p[i].priority);
    }

    preemptive_priority();

    return 0;
}
