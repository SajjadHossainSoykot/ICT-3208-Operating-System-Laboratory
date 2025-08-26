#include <iostream>
#include <iomanip>
using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    bool completed = false;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process processes[n];

    // Input
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter Arrival Time & Burst Time for P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    int currentTime = 0, completedCount = 0;
    float totalWT = 0, totalTAT = 0;

    // SRTF Scheduling Loop (preemptive)
    while (completedCount < n) {
        int idx = -1;
        int minRem = 1e9;

        // Find process with minimum remaining time among arrived ones
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime) {
                if (processes[i].remainingTime < minRem && processes[i].remainingTime > 0) {
                    minRem = processes[i].remainingTime;
                    idx = i;
                } else if (processes[i].remainingTime == minRem && idx != -1) {
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            // Run the selected process for 1 time unit
            processes[idx].remainingTime--;
            currentTime++;

            // If process finishes
            if (processes[idx].remainingTime == 0) {
                processes[idx].completed = true;
                processes[idx].completionTime = currentTime;
                processes[idx].turnAroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;

                totalWT += processes[idx].waitingTime;
                totalTAT += processes[idx].turnAroundTime;

                completedCount++;
            }
        } else {
            currentTime++; // CPU idle
        }
    }

    // Output
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].pid << "\t"
             << processes[i].arrivalTime << "\t"
             << processes[i].burstTime << "\t"
             << processes[i].completionTime << "\t"
             << processes[i].turnAroundTime << "\t"
             << processes[i].waitingTime << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time = " << totalTAT / n;
    cout << "\nAverage Waiting Time = " << totalWT / n << "\n";

    return 0;
}
/*
Output:
Enter number of processes: 5
Enter Arrival Time & Burst Time for P1: 2 6
Enter Arrival Time & Burst Time for P2: 1 3
Enter Arrival Time & Burst Time for P3: 4 2
Enter Arrival Time & Burst Time for P4: 0 5
Enter Arrival Time & Burst Time for P5: 6 4

PID     AT      BT      CT      TAT     WT
P1      2       6       20      18      12
P2      1       3       4       3       0
P3      4       2       6       2       0
P4      0       5       10      10      5
P5      6       4       14      8       4

Average Turnaround Time = 8.20
Average Waiting Time = 4.20
*/