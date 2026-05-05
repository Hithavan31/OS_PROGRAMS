#include <stdio.h>
#include <stdlib.h>

#define N 5

void one_can_eat(int hungry[], int count) {
    int eaten[N] = {0};   // track who has eaten
    int completed = 0;

    while (completed < count) {

        // print only those who are still waiting
        for (int i = 0; i < count; i++) {
            if (!eaten[i]) {
                printf("P %d is waiting\n", hungry[i]);
            }
        }

        // allow ONE philosopher to eat
        for (int i = 0; i < count; i++) {
            if (!eaten[i]) {
                printf("P %d is granted to eat\n", hungry[i]);
                printf("P %d has finished eating\n", hungry[i]);

                eaten[i] = 1;
                completed++;
                break; // only one eats at a time
            }
        }
    }
}

void two_can_eat(int hungry[], int count) {
    int eaten[N] = {0};
    int completed = 0;

    while (completed < count) {

        // show waiting philosophers
        for (int i = 0; i < count; i++) {
            if (!eaten[i]) {
                printf("P %d is waiting\n", hungry[i]);
            }
        }

        int first = -1, second = -1;

        // pick first philosopher
        for (int i = 0; i < count; i++) {
            if (!eaten[i]) {
                first = i;
                break;
            }
        }

        // pick second philosopher
        for (int i = first + 1; i < count; i++) {
            if (!eaten[i]) {
                second = i;
                break;
            }
        }

        if (second != -1) {
            printf("P %d and P %d are granted to eat\n", hungry[first], hungry[second]);

            printf("P %d has finished eating\n", hungry[first]);
            printf("P %d has finished eating\n", hungry[second]);

            eaten[first] = eaten[second] = 1;
            completed += 2;
        } else if (first != -1) {
            printf("P %d is granted to eat\n", hungry[first]);
            printf("P %d has finished eating\n", hungry[first]);

            eaten[first] = 1;
            completed++;
        }
    }
}

int main() {
    int total, hungryCount;
    int hungry[N];

    printf("Enter the total number of philosophers: ");
    scanf("%d", &total);



    int choice;
    while (1) {
         printf("How many are hungry: ");
         scanf("%d", &hungryCount);

        for (int i = 0; i < hungryCount; i++) {
            printf("Enter philosopher %d position (1 to %d): ", i+1, total);
            scanf("%d", &hungry[i]);
        }
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Allow one philosopher to eat at any time\n");
                one_can_eat(hungry, hungryCount);
                break;
            case 2:
                printf("Allow two philosophers to eat at any time\n");
                two_can_eat(hungry, hungryCount);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
