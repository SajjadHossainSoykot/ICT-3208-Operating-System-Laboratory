#include <iostream>
#include <iomanip>
#include <queue>
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
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;

    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter Arrival Time & Burst Time of P" << processes[i].pid << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    queue<int> q;
    int time = 0, completed = 0;
    bool visited[n] = {false};

    // Initially push all processes arriving at time 0
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime == 0) {
            q.push(i);
            visited[i] = true;
        }
    }

    while (completed < n) {
        if (q.empty()) {
            time++; // CPU idle
            for (int i = 0; i < n; i++) {
                if (!visited[i] && processes[i].arrivalTime <= time) {
                    q.push(i);
                    visited[i] = true;
                }
            }
            continue;
        }

        int idx = q.front(); q.pop();

        if (processes[idx].remainingTime > tq) {
            time += tq;
            processes[idx].remainingTime -= tq;
        } else {
            time += processes[idx].remainingTime;
            processes[idx].remainingTime = 0;
            processes[idx].completed = true;
            completed++;

            processes[idx].completionTime = time;
            processes[idx].turnAroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;
        }

        // Add newly arrived processes
        for (int i = 0; i < n; i++) {
            if (!visited[i] && processes[i].arrivalTime <= time) {
                q.push(i);
                visited[i] = true;
            }
        }

        // If current process is not finished, put it back in queue
        if (!processes[idx].completed) {
            q.push(idx);
        }
    }

    // Output
    float totalTAT = 0, totalWT = 0;
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        totalTAT += processes[i].turnAroundTime;
        totalWT += processes[i].waitingTime;
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
Enter Arrival Time & Burst Time of P1: 0 6
Enter Arrival Time & Burst Time of P2: 1 3
Enter Arrival Time & Burst Time of P3: 2 5
Enter Arrival Time & Burst Time of P4: 3 1
Enter Arrival Time & Burst Time of P5: 4 4
Enter Time Quantum: 2

PID     AT      BT      CT      TAT     WT
P1      0       6       16      16      10
P2      1       3       12      11      8
P3      2       5       19      17      12
P4      3       1       9       6       5
P5      4       4       18      14      10

Average Turnaround Time = 12.80
Average Waiting Time = 9.00
*/