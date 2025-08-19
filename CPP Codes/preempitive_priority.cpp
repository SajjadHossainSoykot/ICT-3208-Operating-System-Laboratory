#include <bits/stdc++.h>
using namespace std;

#define MAX 30

int main() {
    int n;
    int at[MAX], bt[MAX], pr[MAX], remaining_bt[MAX]; // remaining burst time
    int wt[MAX], tat[MAX], ct[MAX], pid[MAX];
    int completed[MAX] = {0}; // 0 = not completed, 1 = completed
    int time = 0;   // current CPU time
    int count = 0;  // completed processes

    float total_wt = 0, total_tat = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    // Input priorities, arrival time & burst time
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Priority, Arrival Time & Burst Time of process P" << pid[i] << ": ";
        cin >> pr[i] >> at[i] >> bt[i];
        remaining_bt[i] = bt[i];
    }

    // Preemptive Priority Scheduling
    while (count < n) {
        int idx = -1;
        int mn_pr = 9999; // best (lowest) priority so far

        // Find highest priority process among arrived and not completed ones
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i]) {
                if (pr[i] < mn_pr) {
                    mn_pr = pr[i];
                    idx = i;
                }
                // If same priority, choose earliest arrival
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

            // If process completed
            if (remaining_bt[idx] == 0) {
                completed[idx] = 1;
                count++;
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];   // Turnaround Time
                wt[idx] = tat[idx] - bt[idx];   // Waiting Time
                total_wt += wt[idx];
                total_tat += tat[idx];
            }
        } else {
            time++; // CPU idle
        }
    }

    // Output
    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" 
             << at[i] << "\t" 
             << bt[i] << "\t" 
             << pr[i] << "\t" 
             << ct[i] << "\t" 
             << tat[i] << "\t" 
             << wt[i] << "\n";
    }

    cout << "\nAverage Waiting Time = " << fixed << setprecision(2) << total_wt / n;
    cout << "\nAverage Turnaround Time = " << fixed << setprecision(2) << total_tat / n << "\n";

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