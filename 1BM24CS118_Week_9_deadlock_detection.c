#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], avail[m];
    int finish[n], safe[n];

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Request Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    for(i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int count = 0;
    while(count < n) {
        int found = 0;
        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                for(j = 0; j < m; j++) {
                    if(request[i][j] > avail[j]) {
                        break;
                    }
                }
                if(j == m) {
                    for(k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }
                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if(found == 0) {
            break;
        }
    }

    if(count == n) {
        printf("No Deadlock Detected\n");
        printf("Safe Sequence: ");
        for(i = 0; i < n; i++) {
            printf("P%d ", safe[i]);
        }
    } else {
        printf("Deadlock Detected\n");
        printf("Processes in deadlock: ");
        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                printf("P%d ", i);
            }
        }
    }

    return 0;
}
