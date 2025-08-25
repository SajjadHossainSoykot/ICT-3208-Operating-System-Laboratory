def main():
    n = int(input("Enter the number of processes: "))

    pid = []
    bt = []
    wt = [0] * n
    tat = [0] * n
    pr = []
    at = []
    ct = [0] * n
    completed = [0] * n  # flag to check if process is finished

    # Input priority, arrival time & burst time
    for i in range(n):
        pid.append(i + 1)
        p, a, b = map(int, input(f"Enter Priority, Arrival Time & Burst Time of process P{pid[i]}: ").split())
        pr.append(p)
        at.append(a)
        bt.append(b)

    time = 0
    count = 0
    awt = 0
    atat = 0

    # Non-preemptive Priority Scheduling
    while count < n:
        idx = -1
        min_pr = 9999

        for i in range(n):
            if at[i] <= time and not completed[i]:  # process arrived and not completed
                if pr[i] < min_pr:
                    min_pr = pr[i]
                    idx = i
                elif pr[i] == min_pr:
                    if at[i] < at[idx]:
                        idx = i

        if idx != -1:
            time += bt[idx]
            ct[idx] = time
            tat[idx] = ct[idx] - at[idx]
            wt[idx] = tat[idx] - bt[idx]
            awt += wt[idx]
            atat += tat[idx]
            completed[idx] = 1
            count += 1
        else:
            time += 1  # CPU idle

    # Print process details
    print("\nP\tAT\tBT\tPR\tCT\tTAT\tWT")
    for i in range(n):
        print(f"P{pid[i]}\t{at[i]}\t{bt[i]}\t{pr[i]}\t{ct[i]}\t{tat[i]}\t{wt[i]}")

    # Print averages
    print(f"\nAverage Waiting Time = {awt / n:.2f}")
    print(f"Average Turnaround Time = {atat / n:.2f}")


if __name__ == "__main__":
    main()


# Output
# Enter the number of processes: 3
# Enter Priority, Arrival Time & Burst Time of process P1: 1 2 3
# Enter Priority, Arrival Time & Burst Time of process P2: 1 2 3
# Enter Priority, Arrival Time & Burst Time of process P3: 1 2 3

# P       AT      BT      PR      CT      TAT     WT
# P1      2       3       1       5       3       0
# P2      2       3       1       8       6       3
# P3      2       3       1       11      9       6

# Average Waiting Time = 3.00
# Average Turnaround Time = 6.00