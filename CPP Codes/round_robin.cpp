#include <bits/stdc++.h>
using namespace std;

#define MAX 100

int main() {
    int n, tq;
    int pid[MAX], at[MAX], bt[MAX], rem_bt[MAX], ct[MAX], tat[MAX], wt[MAX];
    int queue[MAX], front = 0, rear = 0;
    int time = 0, completed = 0;
    int visited[MAX] = {0};

    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Time & Burst Time of P" << pid[i] << ": ";
        cin >> at[i] >> bt[i];
        rem_bt[i] = bt[i];
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    // Push first process if it arrives at time 0
    for (int i = 0; i < n; i++) {
        if (at[i] == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) { // No process ready → CPU idle
            time++;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && at[i] <= time) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int i = queue[front++]; // Dequeue process

        if (rem_bt[i] > tq) {
            time += tq;
            rem_bt[i] -= tq;
        } else {
            time += rem_bt[i];
            rem_bt[i] = 0;
            completed++;
            ct[i] = time;
        }

        // Add newly arrived processes to queue
        for (int j = 0; j < n; j++) {
            if (!visited[j] && at[j] <= time) {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        // If current process still needs time, push back into queue
        if (rem_bt[i] > 0) {
            queue[rear++] = i;
        }
    }

    // Calculate TAT & WT
    float sum_tat = 0, sum_wt = 0;
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        sum_tat += tat[i];
        sum_wt += wt[i];
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage TAT = " << fixed << setprecision(2) << sum_tat / n;
    cout << "\nAverage WT  = " << fixed << setprecision(2) << sum_wt / n << "\n";

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