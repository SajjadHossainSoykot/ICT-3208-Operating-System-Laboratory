#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class process{
    public:
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
};
bool compare_arrival(process p1, process p2){
    return p1.arrivalTime<p2.arrivalTime;
}
bool compare_pid(process p1, process p2) {
    return p1.pid < p2.pid;   // for restoring PID order
}

int main(){
    int n;
    cout<<"Enter the Number of Process : ";
    cin>>n;
    vector <process> processes(n);

    for(int i=0; i<n; ++i){
        processes[i].pid=i+1;
        cout << "Enter Arrival and Burst Time for P"<<i+1<< ": ";
        cin >> processes[i].arrivalTime>>processes[i].burstTime;

    }

    sort(processes.begin(),processes.end(),compare_arrival);

    int currentTime=0;
    float totalWT=0, totalTAT=0;

    for(int i=0; i<n; ++i){
        if(currentTime<processes[i].arrivalTime){
            currentTime=processes[i].arrivalTime;
        }

        processes[i].completionTime=currentTime+processes[i].burstTime;
        processes[i].turnAroundTime=processes[i].completionTime-processes[i].arrivalTime;
        processes[i].waitingTime=processes[i].turnAroundTime-processes[i].burstTime;

        currentTime=processes[i].completionTime;
        totalWT+=processes[i].waitingTime;
        totalTAT+=processes[i].turnAroundTime;
    }

    // restore PID order for output
    sort(processes.begin(), processes.end(), compare_pid);

    cout<<"\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].pid << "\t"
             << processes[i].arrivalTime << "\t"
             << processes[i].burstTime << "\t"
             << processes[i].completionTime << "\t"
             << processes[i].turnAroundTime << "\t"
             << processes[i].waitingTime << "\n";
    }

    cout << "\nAverage Turnaround Time = " << totalWT/n<<endl;
    cout << "Average Waiting Time = " << totalTAT/n << endl;
    
}

/*
Output
Enter the number of processes: 6
Enter Priority, Arrival Time, and Burst Time for P1: 2 3 5
Enter Priority, Arrival Time, and Burst Time for P2: 1 2 4
Enter Priority, Arrival Time, and Burst Time for P3: 3 5 1
Enter Priority, Arrival Time, and Burst Time for P4: 4 4 7
Enter Priority, Arrival Time, and Burst Time for P5: 3 1 6
Enter Priority, Arrival Time, and Burst Time for P6: 5 0 2

PID     AT      BT      PR      CT      TAT     WT
P1      3       5       2       11      8       3
P2      2       4       1       6       4       0
P3      5       1       3       18      13      12
P4      4       7       4       25      21      14
P5      1       6       3       17      16      10
P6      0       2       5       2       2       0

Average Waiting Time = 6.5
Average Turnaround Time = 10.6667
*/