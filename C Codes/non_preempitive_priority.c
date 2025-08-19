//non_preemptive priority scheduling
#include<stdio.h>
#define max 30

int main() {
    int i, j, n;
    int bt[max], wt[max], tat[max], pr[max], at[max], ct[max], pid[max];
    int completed[max] = {0}; //flag to check if process is finished
    float awt = 0, atat = 0;
    int time = 0;//current cpu time  
    int count = 0;//Number of completed process

    //Enter the number of process
    printf("Enter the number of  processes: ");
    scanf("%d", &n);

    //input priority, arrival time & burst time
    
    for (i = 0; i < n; i++) {
        pid[i]=i+1;
        printf("Enter Priorities, Arrival Times & Burst Times of process p%d :",pid[i]);
        scanf("%d %d %d", &pr[i],&at[i],&bt[i]);
    } 

    // Non-preemptive Priority Scheduling
    while (count < n) {
        int idx = -1, min_pr = 9999;

        // Select the next process to execute based on priority (and arrival time if needed)
        //less value=highset priority
        for (i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i]) //arrival time ==current cpu time and process not completed
            {
                if (pr[i] < min_pr) {
                    min_pr = pr[i];
                    idx = i;
                }
                // If same priority, choose earlier arrival time
                else if (pr[i] == min_pr) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }
        //turn_arround_time calculation and waiting_time calculation
        if (idx != -1) {
            time += bt[idx];
            //for waiting time and turn arround time calculation
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];  
            wt[idx] = tat[idx] - bt[idx];
            awt += wt[idx];
            atat += tat[idx];
            completed[idx] = 1;
            count++;
        } else {
            time++; // idle time
        }
    }

    printf("\nP\tAT\tBT\tPR\tCT\ttat\twt");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d",
               pid[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", awt / n);
    printf("\nAverage Turnaround Time = %.2f\n", atat / n);


    return 0;
}
/*
Output:
Enter the number of  processes: 3
Enter Priorities, Arrival Times & Burst Times of process p1 :1 2 3 
Enter Priorities, Arrival Times & Burst Times of process p2 :1 2 3
Enter Priorities, Arrival Times & Burst Times of process p3 :1 2 3

P       AT      BT      PR      CT      tat     wt
P1      2       3       1       5       3       0
P2      2       3       1       8       6       3
P3      2       3       1       11      9       6

Average Waiting Time = 3.00
Average Turnaround Time = 6.00
*/