#include <iostream>
#include <iomanip>
using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
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

    // Input processes (Priority → Arrival Time → Burst Time)
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter Priority, Arrival Time and Burst Time for P" << i + 1 << ": ";
        cin >> processes[i].priority >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    int currentTime = 0, completedCount = 0;
    float totalWT = 0, totalTAT = 0;

    // Preemptive Priority Scheduling
    while (completedCount < n) {
        int idx = -1;
        int highestPriority = -1; // now higher value = higher priority

        // Select process with highest priority among arrived processes
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime) {
                if (processes[i].priority > highestPriority) {  // flipped here
                    highestPriority = processes[i].priority;
                    idx = i;
                } else if (processes[i].priority == highestPriority) {
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i; // tie-breaker: earlier arrival
                    }
                }
            }
        }

        if (idx == -1) {
            currentTime++; // CPU idle
        } else {
            // Run selected process for 1 unit
            processes[idx].remainingTime--;
            currentTime++;

            // If process finishes
            if (processes[idx].remainingTime == 0) {
                processes[idx].completed = true;
                completedCount++;

                processes[idx].completionTime = currentTime;
                processes[idx].turnAroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;

                totalWT += processes[idx].waitingTime;
                totalTAT += processes[idx].turnAroundTime;
            }
        }
    }

    // Output
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

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time = " << totalWT / n;
    cout << "\nAverage Turnaround Time = " << totalTAT / n << "\n";

    return 0;
}

/*
Output:
Enter number of processes: 5
Enter Priority, Arrival Time and Burst Time for P1: 2 3 5
Enter Priority, Arrival Time and Burst Time for P2: 1 2 4
Enter Priority, Arrival Time and Burst Time for P3: 3 5 6
Enter Priority, Arrival Time and Burst Time for P4: 4 1 7
Enter Priority, Arrival Time and Burst Time for P5: 3 0 5

PID     AT      BT      PR      CT      TAT     WT
P1      3       5       2       23      20      15
P2      2       4       1       27      25      21
P3      5       6       3       18      13      7
P4      1       7       4       8       7       0
P5      0       5       3       12      12      7

Average Waiting Time = 10.00
Average Turnaround Time = 15.40
*/