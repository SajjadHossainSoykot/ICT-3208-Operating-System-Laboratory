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

    cout << "\nAverage Turnaround Time = " << totalTAT/n<<endl;
    cout << "Average Waiting Time = " << totalWT/n << endl;
    
}

/*
Output

*/