//non_preemptive priority scheduling
#include <bits/stdc++.h>
using namespace std;

#define max 30

int main() {
    int i, j, n;
    int bt[max], wt[max], tat[max], pr[max], at[max], ct[max], pid[max];
    int completed[max] = {0}; // flag to check if process is finished
    float awt = 0, atat = 0;
    int time = 0;   // current CPU time  
    int count = 0;  // Number of completed processes

    // Enter the number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    // Input priority, arrival time & burst time
    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Priority, Arrival Time & Burst Time of process P" << pid[i] << ": ";
        cin >> pr[i] >> at[i] >> bt[i];
    }

    // Non-preemptive Priority Scheduling
    while (count < n) {
        int idx = -1, min_pr = 9999;

        // Select the next process to execute based on priority (and arrival time if needed)
        // smaller value = higher priority
        for (i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i]) // process arrived and not completed
            {
                if (pr[i] < min_pr) {
                    min_pr = pr[i];
                    idx = i;
                }
                // If same priority, choose earlier arrival time
                else if (pr[i] == min_pr) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }

        // Turnaround time and waiting time calculation
        if (idx != -1) {
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            awt += wt[idx];
            atat += tat[idx];
            completed[idx] = 1;
            count++;
        } else {
            time++; // CPU idle time
        }
    }

    // Print process details
    cout << "\nP\tAT\tBT\tPR\tCT\tTAT\tWT";
    for (i = 0; i < n; i++) {
        cout << "\nP" << pid[i] << "\t" 
             << at[i] << "\t" 
             << bt[i] << "\t" 
             << pr[i] << "\t" 
             << ct[i] << "\t" 
             << tat[i] << "\t" 
             << wt[i];
    }

    // Print averages
    cout << "\n\nAverage Waiting Time = " << awt / n;
    cout << "\nAverage Turnaround Time = " << atat / n << endl;

    return 0;
}

/*
Output:
Enter the number of  processes: 3
Enter Priorities, Arrival Times & Burst Times of process p1 :1 2 3 
Enter Priorities, Arrival Times & Burst Times of process p2 :1 2 3
Enter Priorities, Arrival Times & Burst Times of process p3 :1 2 3

P       AT      BT      PR      CT      tat     wt
P1      2       3       1       5       3       0
P2      2       3       1       8       6       3
P3      2       3       1       11      9       6

Average Waiting Time = 3.00
Average Turnaround Time = 6.00
*/