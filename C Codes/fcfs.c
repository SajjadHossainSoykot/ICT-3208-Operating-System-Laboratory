#include <stdio.h>

int main()
{
    int n, i, j, time = 0;
    int pid[10], at[10], bt[10];
    int ct[10], tat[10], wt[10];
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input PID, AT, BT
    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Enter Arrival and Burst Time for P%d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }

    // Copy original arrays to sort based on arrival time
    int orig_pid[10], orig_at[10], orig_bt[10];
    for (i = 0; i < n; i++)
    {
        orig_pid[i] = pid[i];
        orig_at[i] = at[i];
        orig_bt[i] = bt[i];
    }

    // Sort by Arrival Time
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (at[i] > at[j])
            {
                int temp;
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    // Calculate Completion, Turnaround, Waiting Time on orig arrays
    time = 0;
    for (i = 0; i < n; i++)
    {
        if (time < at[i])
        {
            time = at[i];
        }
        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        time = ct[i];
    }
    int orig_ct[10], orig_tat[10], orig_wt[10];
    // Map back the results to original PID order
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (orig_pid[i] == pid[j])
            {
                orig_ct[i] = ct[j];
                orig_tat[i] = tat[j];
                orig_wt[i] = wt[j];
                avg_tat += orig_tat[i];
                avg_wt += orig_wt[i];
                break;
            }
        }
    }

    // Print output in original PID order
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", orig_pid[i], orig_at[i], orig_bt[i], orig_ct[i], orig_tat[i], orig_wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
}

/*
Output:
Enter number of processes: 3
Enter Arrival and Burst Time for P1: 1 2
Enter Arrival and Burst Time for P2: 2 3
Enter Arrival and Burst Time for P3: 4 5

PID     AT      BT      CT      TAT     WT
P1      1       2       3       2       0
P2      2       3       6       4       1
P3      4       5       11      7       2

Average Turnaround Time = 4.33
Average Waiting Time = 1.00
*/
