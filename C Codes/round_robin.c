#include <stdio.h>

#define MAX 100

int main()
{
    int n, tq;
    int pid[MAX], at[MAX], bt[MAX], rem_bt[MAX], ct[MAX], tat[MAX], wt[MAX];
    int queue[MAX], front = 0, rear = 0;
    int time = 0, completed = 0;
    int visited[MAX] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Enter Arrival Time & Burst Time  of P%d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
        rem_bt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Push first process if it arrives at time 0
    for (int i = 0; i < n; i++)
    {
        if (at[i] == 0)
        {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n)
    {
        if (front == rear)
        { // No process ready → CPU idle
            time++;
            for (int i = 0; i < n; i++)
            {
                if (!visited[i] && at[i] <= time)
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int i = queue[front++]; // Dequeue process

        if (rem_bt[i] > tq)
        {
            time += tq;
            rem_bt[i] -= tq;
        }
        else
        {
            time += rem_bt[i];
            rem_bt[i] = 0;
            completed++;
            ct[i] = time;
        }

        // Add newly arrived processes to queue
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && at[j] <= time)
            {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        // If current process still needs time, push back into queue
        if (rem_bt[i] > 0)
        {
            queue[rear++] = i;
        }
    }

    // Calculate TAT & WT
    float sum_tat = 0, sum_wt = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        sum_tat += tat[i];
        sum_wt += wt[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT = %.2f", sum_tat / n);
    printf("\nAverage WT  = %.2f\n", sum_wt / n);

    return 0;
}

/*
Output:
Enter number of processes: 3
Enter Arrival Time & Burst Time  of P1: 1 2
Enter Arrival Time & Burst Time  of P2: 3 4
Enter Arrival Time & Burst Time  of P3: 5 6
Enter Time Quantum: 1

PID     AT      BT      CT      TAT     WT
P1      1       2       3       2       0
P2      3       4       9       6       2
P3      5       6       13      8       2

Average TAT = 5.33
Average WT  = 1.33
*/