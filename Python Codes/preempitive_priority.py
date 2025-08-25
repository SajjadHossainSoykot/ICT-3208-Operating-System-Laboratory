def main():
    n = int(input("Enter number of processes: "))

    pid = []
    at = []
    bt = []
    pr = []
    remaining_bt = []
    completed = [0] * n
    ct = [0] * n
    tat = [0] * n
    wt = [0] * n

    total_wt = 0
    total_tat = 0
    time = 0
    count = 0

    # Input priorities, arrival time & burst time
    for i in range(n):
        pid.append(i + 1)
        p, a, b = map(int, input(f"Enter Priority, Arrival Time & Burst Time of process P{pid[i]}: ").split())
        pr.append(p)
        at.append(a)
        bt.append(b)
        remaining_bt.append(b)

    # Preemptive Priority Scheduling
    while count < n:
        idx = -1
        mn_pr = 9999  # lowest priority value (higher priority)

        # Select process with highest priority among arrived and not completed
        for i in range(n):
            if at[i] <= time and not completed[i]:
                if pr[i] < mn_pr:
                    mn_pr = pr[i]
                    idx = i
                elif pr[i] == mn_pr:
                    if at[i] < at[idx]:
                        idx = i

        if idx != -1:
            remaining_bt[idx] -= 1
            time += 1

            # If process completed
            if remaining_bt[idx] == 0:
                completed[idx] = 1
                count += 1
                ct[idx] = time
                tat[idx] = ct[idx] - at[idx]
                wt[idx] = tat[idx] - bt[idx]
                total_tat += tat[idx]
                total_wt += wt[idx]
        else:
            time += 1  # CPU idle

    # Output
    print("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT")
    for i in range(n):
        print(f"P{pid[i]}\t{at[i]}\t{bt[i]}\t{pr[i]}\t{ct[i]}\t{tat[i]}\t{wt[i]}")

    print(f"\nAverage Waiting Time = {total_wt / n:.2f}")
    print(f"Average Turnaround Time = {total_tat / n:.2f}")


if __name__ == "__main__":
    main()


# Output
# Enter number of processes: 3
# Enter Priority, Arrival Time & Burst Time of process P1: 1 2 3
# Enter Priority, Arrival Time & Burst Time of process P2: 1 2 3
# Enter Priority, Arrival Time & Burst Time of process P3: 1 2 3

# PID     AT      BT      PR      CT      TAT     WT
# P1      2       3       1       5       3       0
# P2      2       3       1       8       6       3
# P3      2       3       1       11      9       6

# Average Waiting Time = 3.00
# Average Turnaround Time = 6.00