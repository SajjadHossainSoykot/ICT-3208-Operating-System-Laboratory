#include <iostream>
#include <iomanip>
using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
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
        cout << "Enter Arrival Time and Burst Time for P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    int currentTime = 0, completedCount = 0;
    float totalWT = 0, totalTAT = 0;

    // Non-preemptive SJF Scheduling
    while (completedCount < n) {
        int idx = -1;
        int minBT = 1e9;

        // Find process with smallest burst time among arrived and incomplete processes
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime < minBT) {
                    minBT = processes[i].burstTime;
                    idx = i;
                } else if (processes[i].burstTime == minBT) {
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            currentTime++; // CPU idle
        } else {
            // Execute process fully (non-preemptive)
            currentTime += processes[idx].burstTime;
            processes[idx].completionTime = currentTime;
            processes[idx].turnAroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;

            processes[idx].completed = true;
            completedCount++;

            totalWT += processes[idx].waitingTime;
            totalTAT += processes[idx].turnAroundTime;
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
Enter Arrival Time and Burst Time for P1: 4 5 
Enter Arrival Time and Burst Time for P2: 0 2
Enter Arrival Time and Burst Time for P3: 1 5
Enter Arrival Time and Burst Time for P4: 6 7
Enter Arrival Time and Burst Time for P5: 2 3

PID     AT      BT      CT      TAT     WT
P1      4       5       15      11      6
P2      0       2       2       2       0
P3      1       5       10      9       4
P4      6       7       22      16      9
P5      2       3       5       3       0

Average Turnaround Time = 8.20
Average Waiting Time = 3.80
*/