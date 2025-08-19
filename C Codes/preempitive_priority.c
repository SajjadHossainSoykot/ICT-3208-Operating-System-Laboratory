//preemptive priority scheduling
#include <stdio.h>

#define MAX 30

int main() {
    int n;
    int at[MAX], bt[MAX], pr[MAX], remaining_bt[MAX];// How much time remains for each process to complete (initialized to burst time).
    int wt[MAX], tat[MAX], ct[MAX], pid[MAX];
    int completed[MAX] = {0};//Array to track whether each process is completed (0 = not completed, 1 = completed)
    int time = 0;//current cpu time
    int count = 0;//Number of completed process

    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    //input Priorities, arrival time & burst time

    
    for (int i = 0; i < n; i++) {
        pid[i]=i+1;
        printf("Enter Priorities, Arrival Times & Burst Times of process p%d :",pid[i]);
        scanf("%d %d %d", &pr[i],&at[i],&bt[i]);
        remaining_bt[i] = bt[i];
    } 
//preemptive Priority Scheduling
    while (count < n) {
        int idx = -1;
        int mn_pr = 9999;// stores the best (lowest) priority found so far, initialized to a large number.

        // Find process with highest priority (lowest number = higher priority)
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i]) {
                if (pr[i] < mn_pr) {
                    mn_pr = pr[i];
                    idx = i;
                }
                // If same priority, choose by arrival time
                else if (pr[i] == mn_pr) {
                     if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            remaining_bt[idx]--;
            time++;

            //calculate completion time,waiting time and turn arround time
            if (remaining_bt[idx] == 0) {
                completed[idx] = 1;
                count++;
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                total_wt += wt[idx];
                total_tat += tat[idx];
            }
        } 
        
        else {
            // No process available at this time
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
} 
/*
Output:
Enter number of processes: 3
Enter Priorities, Arrival Times & Burst Times of process p1 :1 2 3
Enter Priorities, Arrival Times & Burst Times of process p2 :1 2 3
Enter Priorities, Arrival Times & Burst Times of process p3 :1 2 3

PID     AT      BT      PR      CT      TAT     WT
P1      2       3       1       5       3       0
P2      2       3       1       8       6       3
P3      2       3       1       11      9       6

Average Waiting Time = 3.00
Average Turnaround Time = 6.00
*/