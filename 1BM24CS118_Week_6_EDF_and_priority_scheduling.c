#include <stdio.h>

#define MAX 10

typedef struct {
    int id;
    int execution;
    int period;
    int deadline;

    int remaining;
    int next_release;
    int abs_deadline;
} Task;

Task tasks[MAX];
int n;


void reset_tasks() {
    for (int i = 0; i < n; i++) {
        tasks[i].remaining = 0;
        tasks[i].next_release = 0;
        tasks[i].abs_deadline = tasks[i].deadline;
    }
}


void release_tasks(int t) {
    for (int i = 0; i < n; i++) {
        if (t == tasks[i].next_release) {
            tasks[i].remaining = tasks[i].execution;
            tasks[i].abs_deadline = t + tasks[i].deadline;
            tasks[i].next_release += tasks[i].period;
        }
    }
}


void check_deadlines(int t) {
    for (int i = 0; i < n; i++) {
        if (tasks[i].remaining > 0 && t >= tasks[i].abs_deadline) {
            printf("⚠️ Task %d MISSED deadline at time %d\n", tasks[i].id, t);
            tasks[i].remaining = 0; // drop job
        }
    }
}


void edf(int time_limit) {
    printf("\n--- Earliest Deadline First Scheduling ---\n");

    reset_tasks();

    for (int t = 0; t < time_limit; t++) {
        release_tasks(t);
        check_deadlines(t);

        int selected = -1;
        int earliest_deadline = 9999;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0 &&
                tasks[i].abs_deadline < earliest_deadline) {
                earliest_deadline = tasks[i].abs_deadline;
                selected = i;
            }
        }

        if (selected != -1) {
            printf("Time %d -> Task %d\n", t, tasks[selected].id);
            tasks[selected].remaining--;
        } else {
            printf("Time %d -> Idle\n", t);
        }
    }
}

void proportional_scheduling(int time_limit) {
    printf("\n--- Proportional Scheduling (Weighted RR) ---\n");

    reset_tasks();

    int total_exec = 0;
    for (int i = 0; i < n; i++) {
        total_exec += tasks[i].execution;
    }

    int turn = 0;

    for (int t = 0; t < time_limit; t++) {
        release_tasks(t);
        check_deadlines(t);

        int found = 0;

        for (int i = 0; i < n; i++) {
            int idx = (turn + i) % n;

            if (tasks[idx].remaining > 0) {
                printf("Time %d -> Task %d\n", t, tasks[idx].id);
                tasks[idx].remaining--;
                turn = idx + 1;
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Time %d -> Idle\n", t);
        }
    }
}


int main() {
    int time_limit;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nTask %d:\n", i + 1);
        tasks[i].id = i + 1;

        printf("Execution Time: ");
        scanf("%d", &tasks[i].execution);

        printf("Period: ");
        scanf("%d", &tasks[i].period);

        printf("Relative Deadline: ");
        scanf("%d", &tasks[i].deadline);
    }

    printf("\nEnter simulation time: ");
    scanf("%d", &time_limit);


    edf(time_limit);
    proportional_scheduling(time_limit);

    return 0;
}
