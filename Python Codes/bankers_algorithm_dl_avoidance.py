def calculate_need(max_demand, allocation, n, m):
    need = [[0] * m for _ in range(n)]
    for i in range(n):
        for j in range(m):
            need[i][j] = max_demand[i][j] - allocation[i][j]
    return need


def is_safe(n, m, allocation, max_demand, available):
    need = calculate_need(max_demand, allocation, n, m)
    work = available[:]
    finish = [False] * n
    safe_sequence = []

    while len(safe_sequence) < n:
        found = False
        for i in range(n):
            if not finish[i] and all(need[i][j] <= work[j] for j in range(m)):
                for j in range(m):
                    work[j] += allocation[i][j]
                safe_sequence.append(i)
                finish[i] = True
                found = True
        if not found:
            return False, []
    return True, safe_sequence


def request_resources(process_id, request, n, m, allocation, max_demand, available):
    need = calculate_need(max_demand, allocation, n, m)

    if any(request[j] > need[process_id][j] for j in range(m)):
        print("Error: Process has exceeded its maximum claim.")
        return False

    if any(request[j] > available[j] for j in range(m)):
        print("Error: Resources not available.")
        return False

    # Tentative allocation
    for j in range(m):
        available[j] -= request[j]
        allocation[process_id][j] += request[j]
        need[process_id][j] -= request[j]

    safe, seq = is_safe(n, m, allocation, max_demand, available)
    if safe:
        print(f"Request granted. Safe sequence: {['P'+str(p) for p in seq]}")
        return True
    else:
        print("Request cannot be granted (would lead to unsafe state).")
        # Rollback
        for j in range(m):
            available[j] += request[j]
            allocation[process_id][j] -= request[j]
            need[process_id][j] += request[j]
        return False


# ----------- Main ------------
if __name__ == "__main__":
    n = int(input("Enter number of processes: "))
    m = int(input("Enter number of resources: "))

    allocation = []
    print("Enter Allocation Matrix:")
    for i in range(n):
        allocation.append(list(map(int, input().split())))

    max_demand = []
    print("Enter Max Matrix:")
    for i in range(n):
        max_demand.append(list(map(int, input().split())))

    available = list(map(int, input("Enter Available Resources: ").split()))

    safe, seq = is_safe(n, m, allocation, max_demand, available)
    if safe:
        print(f"System is in a safe state. Safe sequence: {['P'+str(p) for p in seq]}")
    else:
        print("System is NOT in a safe state.")

    # Example resource request
    ch = input("Do you want to make a request? (y/n): ")
    if ch.lower() == 'y':
        pid = int(input("Enter process id: "))
        request = list(map(int, input("Enter request vector: ").split()))
        request_resources(pid, request, n, m, allocation, max_demand, available)


# Output:
# Enter number of processes: 5
# Enter number of resources: 3
# Enter Allocation Matrix:
# 0 1 0
# 2 0 0
# 3 0 2
# 2 1 1
# 0 0 2
# Enter Max Matrix:
# 7 5 3
# 3 2 2
# 9 0 2
# 2 2 2
# 4 3 3
# Enter Available Resources: 3 3 2
# System is in a safe state. Safe sequence: ['P1', 'P3', 'P4', 'P0', 'P2']
# Do you want to make a request? (y/n): y
# Enter process id: 1
# Enter request vector: 1 0 2
# Request granted. Safe sequence: ['P1', 'P3', 'P4', 'P0', 'P2']
