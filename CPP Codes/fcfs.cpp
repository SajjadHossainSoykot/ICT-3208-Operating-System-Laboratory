#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, i, j, time = 0;
    int pid[10], at[10], bt[10];
    int ct[10], tat[10], wt[10];
    float avg_tat = 0, avg_wt = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    // Input PID, AT, BT
    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter Arrival and Burst Time for P" << pid[i] << ": ";
        cin >> at[i] >> bt[i];
    }

    // Copy original arrays
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
                swap(at[i], at[j]);
                swap(bt[i], bt[j]);
                swap(pid[i], pid[j]);
            }
        }
    }

    // Calculate Completion, Turnaround, Waiting Time
    time = 0;
    for (i = 0; i < n; i++)
    {
        if (time < at[i])
            time = at[i];

        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        time = ct[i];
    }

    int orig_ct[10], orig_tat[10], orig_wt[10];
    // Map back results
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

    // Print output
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (i = 0; i < n; i++)
    {
        cout << "P" << orig_pid[i] << "\t"
             << orig_at[i] << "\t"
             << orig_bt[i] << "\t"
             << orig_ct[i] << "\t"
             << orig_tat[i] << "\t"
             << orig_wt[i] << "\n";
    }

    cout << "\nAverage Turnaround Time = " << avg_tat / n;
    cout << "\nAverage Waiting Time = " << avg_wt / n << endl;

    return 0;
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
