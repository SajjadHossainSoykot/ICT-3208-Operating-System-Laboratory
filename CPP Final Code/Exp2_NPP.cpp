#include <iostream>
using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    bool completed = false;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter Priority, Arrival Time, and Burst Time for P" << i + 1 << ": ";
        cin >> processes[i].priority >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    int completedCount = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    while (completedCount < n) {
        int idx = -1;
        int highestPriority = 1e9; // smaller value = higher priority

        // Find next process to execute
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime) {
                if (processes[i].priority < highestPriority) {
                    idx = i;
                    highestPriority = processes[i].priority;
                } else if (processes[i].priority == highestPriority) {
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            currentTime++; // CPU idle
        } else {
            Process &p = processes[idx];
            p.completionTime = currentTime + p.burstTime;
            p.turnAroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnAroundTime - p.burstTime;
            p.completed = true;

            totalWT += p.waitingTime;
            totalTAT += p.turnAroundTime;

            currentTime = p.completionTime;
            completedCount++;
        }
    }

    // Print results
    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].pid << "\t"
             << processes[i].arrivalTime << "\t"
             << processes[i].burstTime << "\t"
             << processes[i].priority << "\t"
             << processes[i].completionTime << "\t"
             << processes[i].turnAroundTime << "\t"
             << processes[i].waitingTime << "\n";
    }

    cout << "\nAverage Waiting Time = " << totalWT / n;
    cout << "\nAverage Turnaround Time = " << totalTAT / n << endl;

    return 0;
}
/*
Output
Enter the number of processes: 3
Enter Priority, Arrival Time, and Burst Time for P1: 3 1 3
Enter Priority, Arrival Time, and Burst Time for P2: 2 2 2
Enter Priority, Arrival Time, and Burst Time for P3: 1 3 1

PID     AT      BT      PR      CT      TAT     WT
P1      1       3       3       4       3       0
P2      2       2       2       7       5       3
P3      3       1       1       5       2       1

Average Waiting Time = 1.33333
Average Turnaround Time = 3.33333
*/