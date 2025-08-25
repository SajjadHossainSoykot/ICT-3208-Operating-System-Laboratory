def main():
    n = int(input("Enter number of processes: "))

    pid = []
    at = []
    bt = []

    # Input PID, AT, BT
    for i in range(n):
        pid.append(i + 1)
        a, b = map(int, input(f"Enter Arrival and Burst Time for P{pid[i]}: ").split())
        at.append(a)
        bt.append(b)

    # Copy original arrays
    orig_pid = pid[:]
    orig_at = at[:]
    orig_bt = bt[:]

    # Sort by Arrival Time
    for i in range(n - 1):
        for j in range(i + 1, n):
            if at[i] > at[j]:
                at[i], at[j] = at[j], at[i]
                bt[i], bt[j] = bt[j], bt[i]
                pid[i], pid[j] = pid[j], pid[i]

    # Calculate Completion, Turnaround, Waiting Time
    ct = [0] * n
    tat = [0] * n
    wt = [0] * n
    time = 0

    for i in range(n):
        if time < at[i]:
            time = at[i]

        ct[i] = time + bt[i]
        tat[i] = ct[i] - at[i]
        wt[i] = tat[i] - bt[i]
        time = ct[i]

    # Map back results
    orig_ct = [0] * n
    orig_tat = [0] * n
    orig_wt = [0] * n
    avg_tat = 0
    avg_wt = 0

    for i in range(n):
        for j in range(n):
            if orig_pid[i] == pid[j]:
                orig_ct[i] = ct[j]
                orig_tat[i] = tat[j]
                orig_wt[i] = wt[j]
                avg_tat += orig_tat[i]
                avg_wt += orig_wt[i]
                break

    # Print output
    print("\nPID\tAT\tBT\tCT\tTAT\tWT")
    for i in range(n):
        print(f"P{orig_pid[i]}\t{orig_at[i]}\t{orig_bt[i]}\t{orig_ct[i]}\t{orig_tat[i]}\t{orig_wt[i]}")

    print(f"\nAverage Turnaround Time = {avg_tat / n:.2f}")
    print(f"Average Waiting Time = {avg_wt / n:.2f}")


if __name__ == "__main__":
    main()


# Output
# Enter number of processes: 3
# Enter Arrival and Burst Time for P1: 1 2
# Enter Arrival and Burst Time for P2: 2 3
# Enter Arrival and Burst Time for P3: 4 5

# PID     AT      BT      CT      TAT     WT
# P1      1       2       3       2       0
# P2      2       3       6       4       1
# P3      4       5       11      7       2

# Average Turnaround Time = 4.33
# Average Waiting Time = 1.00
