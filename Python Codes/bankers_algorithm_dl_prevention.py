def main():
    # Input: number of processes and resources
    n = int(input("Enter number of processes: "))
    m = int(input("Enter number of resources: "))

    # Max matrix input
    maxMat = []
    print("Enter Max Matrix:")
    for i in range(n):
        row = list(map(int, input().split()))
        maxMat.append(row)

    # Available resources input
    avail = list(map(int, input("Enter Available Resources:\n").split()))

    print("\n--- Deadlock Prevention Simulation ---")

    for i in range(n):
        print(f"\nProcess P{i} requesting all resources at once...")
        canAllocate = True

        # Check if resources can be allocated
        for j in range(m):
            if maxMat[i][j] > avail[j]:
                canAllocate = False
                break

        if canAllocate:
            print(f"Resources allocated to P{i}.")
            for j in range(m):
                avail[j] -= maxMat[i][j]

            print(f"Process P{i} finished and released resources.")
            for j in range(m):
                avail[j] += maxMat[i][j]
        else:
            print(f"Process P{i} must wait (cannot hold some and wait for others).")


if __name__ == "__main__":
    main()
