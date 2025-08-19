#include<bits/stdc++.h>
using namespace std;

#define MAX 20

int main() {
    int n, i, time = 0, count = 0;
    int pid[MAX], at[MAX], bt[MAX], rem_bt[MAX], ct[MAX], tat[MAX], wt[MAX];
    int completed[MAX] = {0};
    float avg_tat = 0, avg_wt = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    for(i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Times & Burst Times of process p" << pid[i] << " : ";
        cin >> at[i] >> bt[i];
        rem_bt[i] = bt[i];
    }

    while (count < n) {
        int idx = -1;
        int min_rem = 9999;

        // select process with minimum remaining time among arrived & not completed
        for (i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i]) {
                if (rem_bt[i] < min_rem && rem_bt[i] > 0) {
                    min_rem = rem_bt[i];
                    idx = i;
                }
                // tie-breaker: earlier arrival
                else if (rem_bt[i] == min_rem && idx != -1) {
                    if (at[i] < at[idx]) idx = i;
                }
            }
        }

        if (idx != -1) {
            // run selected process for 1 time unit
            rem_bt[idx]--;
            time++;

            // if process finished
            if (rem_bt[idx] == 0) {
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];

                avg_tat += tat[idx];
                avg_wt += wt[idx];

                completed[idx] = 1;
                count++;
            }
        } else {
            // no process available -> CPU idle, advance time
            time++;
        }
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t" 
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
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