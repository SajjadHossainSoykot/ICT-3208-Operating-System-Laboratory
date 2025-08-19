#include <stdio.h>

#define MAX 20

int main() {
    int n, i, idx;
    int pid[MAX], at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX], completed[MAX] = {0};
    int time = 0, count = 0;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    //input arrival time & burst time
    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Times & Burst Times of process p%d :",pid[i]);
        scanf("%d %d",&at[i],&bt[i]);
    }

    while (count < n) {
        idx = -1;
        int min_bt = 9999;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i]) {
                if (bt[i] < min_bt) {
                    min_bt = bt[i];
                    idx = i;
                }
                else if (bt[i]== min_bt)
                {
                    if(at[i]<at[idx])
                    {
                        idx=i;
                    }
                }
                
            }
        }

        if (idx != -1) {
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            avg_tat += tat[idx];
            avg_wt += wt[idx];

            completed[idx] = 1;
            count++;
        } else {
            time++; // CPU idle
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);

    return 0;
}
/*
Output:
Enter number of processes: 3
Enter Arrival Times & Burst Times of process p1 :1 2
Enter Arrival Times & Burst Times of process p2 :2 3
Enter Arrival Times & Burst Times of process p3 :4 5

PID     AT      BT      CT      TAT     WT
P1      1       2       3       2       0
P2      2       3       6       4       1
P3      4       5       11      7       2

Average Turnaround Time: 4.33
Average Waiting Time: 1.00
*/