#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 5;
int x = 0;

void wait(int *s)
{
    (*s)--;
}

void signal(int *s)
{
    (*s)++;
}

void producer()
{
    if (empty != 0)
    {
        wait(&empty);   // decrease empty slots
        wait(&mutex);   // enter critical section

        x++;
        printf("Producer has produced: Item %d\n", x);

        signal(&mutex); // leave critical section
        signal(&full);  // increase filled slots
    }
    else
    {
        printf("Buffer is full!\n");
    }
}

void consumer()
{
    if (full != 0)
    {
        wait(&full);    // decrease filled slots
        wait(&mutex);   // enter critical section

        printf("Consumer has consumed: Item %d\n", x);
        x--;

        signal(&mutex); // leave critical section
        signal(&empty); // increase empty slots
    }
    else
    {
        printf("Buffer is empty!\n");
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\nEnter 1.Producer 2.Consumer 3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
