def main():
    n = int(input("Enter number of processes: "))

    pid = []
    at = []
    bt = []
    rem_bt = []
    ct = [0] * n
    tat = [0] * n
    wt = [0] * n
    completed = [0] * n

    avg_tat = 0
    avg_wt = 0
    time = 0
    count = 0

    # Input
    for i in range(n):
        pid.append(i + 1)
        a, b = map(int, input(f"Enter Arrival Time & Burst Time of process P{pid[i]}: ").split())
        at.append(a)
        bt.append(b)
        rem_bt.append(b)

    # Preemptive SJF (SRTF)
    while count < n:
        idx = -1
        min_rem = 9999

        # Find process with minimum remaining time among arrived ones
        for i in range(n):
            if at[i] <= time and not completed[i]:
                if rem_bt[i] < min_rem and rem_bt[i] > 0:
                    min_rem = rem_bt[i]
                    idx = i
                elif rem_bt[i] == min_rem and idx != -1:
                    if at[i] < at[idx]:
                        idx = i

        if idx != -1:
            # Run selected process for 1 time unit
            rem_bt[idx] -= 1
            time += 1

            # If process completed
            if rem_bt[idx] == 0:
                ct[idx] = time
                tat[idx] = ct[idx] - at[idx]
                wt[idx] = tat[idx] - bt[idx]

                avg_tat += tat[idx]
                avg_wt += wt[idx]

                completed[idx] = 1
                count += 1
        else:
            # CPU idle
            time += 1

    # Output
    print("\nPID\tAT\tBT\tCT\tTAT\tWT")
    for i in range(n):
        print(f"P{pid[i]}\t{at[i]}\t{bt[i]}\t{ct[i]}\t{tat[i]}\t{wt[i]}")

    print(f"\nAverage Turnaround Time: {avg_tat / n:.2f}")
    print(f"Average Waiting Time: {avg_wt / n:.2f}")


if __name__ == "__main__":
    main()

# Output:
# Enter number of processes: 3
# Enter Arrival Time & Burst Time of process P1: 1 2
# Enter Arrival Time & Burst Time of process P2: 2 3 
# Enter Arrival Time & Burst Time of process P3: 4 5

# PID     AT      BT      CT      TAT     WT
# P1      1       2       3       2       0
# P2      2       3       6       4       1
# P3      4       5       11      7       2

# Average Turnaround Time: 4.33
# Average Waiting Time: 1.00