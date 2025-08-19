#include <bits/stdc++.h>
using namespace std;

#define MAX 20

int main() {
    int n, i, idx;
    int pid[MAX], at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX], completed[MAX] = {0};
    int time = 0, count = 0;
    float avg_tat = 0, avg_wt = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    // Input arrival time & burst time
    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Time & Burst Time of process P" << pid[i] << ": ";
        cin >> at[i] >> bt[i];
    }

    // Non-preemptive Shortest Job First (SJF)
    while (count < n) {
        idx = -1;
        int min_bt = 9999;

        // Find process with smallest burst time among arrived ones
        for (i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i]) {
                if (bt[i] < min_bt) {
                    min_bt = bt[i];
                    idx = i;
                } else if (bt[i] == min_bt) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            // Execute selected process
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];   // Turnaround Time
            wt[idx] = tat[idx] - bt[idx];   // Waiting Time

            avg_tat += tat[idx];
            avg_wt += wt[idx];

            completed[idx] = 1;
            count++;
        } else {
            time++; // CPU idle
        }
    }

    // Print results
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" 
             << at[i] << "\t" 
             << bt[i] << "\t" 
             << ct[i] << "\t" 
             << tat[i] << "\t" 
             << wt[i] << "\n";
    }

    cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << avg_tat / n;
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << avg_wt / n << "\n";

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