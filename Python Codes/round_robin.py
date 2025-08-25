def round_robin(n, processes, tq):
    at = [processes[i][0] for i in range(n)]   # Arrival times
    bt = [processes[i][1] for i in range(n)]   # Burst times
    rem_bt = bt[:]                             # Remaining burst times
    ct = [0] * n                               # Completion times
    tat = [0] * n                              # Turnaround times
    wt = [0] * n                               # Waiting times
    visited = [0] * n                          # Process visited status
    
    time = 0
    complete = 0
    queue = []
    
    # Push processes that arrive at time 0
    for i in range(n):
        if at[i] <= time and not visited[i]:
            queue.append(i)
            visited[i] = 1
    
    # Scheduling loop
    while complete < n:
        if not queue:
            time += 1  # CPU idle
            for i in range(n):
                if at[i] <= time and not visited[i]:
                    queue.append(i)
                    visited[i] = 1
            continue
        
        i = queue.pop(0)  # Dequeue process
        
        if rem_bt[i] <= tq:
            time += rem_bt[i]
            rem_bt[i] = 0
            complete += 1
            ct[i] = time
        else:
            time += tq
            rem_bt[i] -= tq
        
        # Push newly arrived processes into queue
        for j in range(n):
            if at[j] <= time and not visited[j] and rem_bt[j] > 0:
                queue.append(j)
                visited[j] = 1
        
        # If current process not finished, push it back
        if rem_bt[i] > 0:
            queue.append(i)
    
    # Calculate TAT and WT
    for i in range(n):
        tat[i] = ct[i] - at[i]
        wt[i] = tat[i] - bt[i]
    
    # Print results
    print("\nPID\tAT\tBT\tCT\tTAT\tWT")
    for i in range(n):
        print(f"P{i+1}\t{at[i]}\t{bt[i]}\t{ct[i]}\t{tat[i]}\t{wt[i]}")
    
    avg_tat = sum(tat) / n
    avg_wt = sum(wt) / n
    print(f"\nAverage TAT = {avg_tat:.2f}")
    print(f"Average WT = {avg_wt:.2f}")


# Example run (same as your C++ test case)
if __name__ == "__main__":
    n = int(input("Enter number of processes: "))
    processes = []
    for i in range(n):
        at = int(input(f"Enter Arrival Time of P{i+1}: "))
        bt = int(input(f"Enter Burst Time of P{i+1}: "))
        processes.append((at, bt))
    
    tq = int(input("Enter Time Quantum: "))
    round_robin(n, processes, tq)


# Output:
# Enter number of processes: 3
# Enter Arrival Time of P1: 1
# Enter Burst Time of P1: 2
# Enter Arrival Time of P2: 3
# Enter Burst Time of P2: 4
# Enter Arrival Time of P3: 5
# Enter Burst Time of P3: 6
# Enter Time Quantum: 1

# PID     AT      BT      CT      TAT     WT
# P1      1       2       3       2       0
# P2      3       4       9       6       2
# P3      5       6       13      8       2

# Average TAT = 5.33
# Average WT = 1.33