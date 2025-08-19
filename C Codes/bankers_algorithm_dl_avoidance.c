#include <stdio.h>

int n, m; // Global for convenience
int alloc[20][20], max[20][20], need[20][20], avail[20];

// Function to check safe state and print sequence
int isSafe()
{
    int work[20], finish[20], safeSeq[20];
    int i, j, k, count = 0;

    // Initialize work and finish
    for (i = 0; i < m; i++)
        work[i] = avail[i];
    for (i = 0; i < n; i++)
        finish[i] = 0;

    while (count < n)
    {
        int found = 0;
        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int canExecute = 1;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canExecute = 0;
                        break;
                    }
                }
                if (canExecute)
                {
                    for (k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
        {
            printf("\nSystem is NOT in a safe state.\n");
            return 0; // Not safe
        }
    }

    printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    for (i = 0; i < n; i++)
    {
        printf("P%d", safeSeq[i]);
        if (i != n - 1)
            printf(" -> ");
    }
    printf("\n");
    return 1; // Safe
}

int main()
{
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("\nNeed Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    // Check initial safe state
    if (!isSafe())
    {
        printf("\nSystem is NOT in a safe state.\n");
        return 0;
    }

    // Resource request handling
    int reqProcess;
    printf("\nEnter the process number making a request (0-%d): ", n - 1);
    scanf("%d", &reqProcess);

    int request[20];
    printf("Enter request for each resource: ");
    for (i = 0; i < m; i++)
        scanf("%d", &request[i]);

    // Check 1: Request <= Need
    for (i = 0; i < m; i++)
    {
        if (request[i] > need[reqProcess][i])
        {
            printf("\nError: Process has exceeded its maximum claim.\n");
            return 0;
        }
    }

    // Check 2: Request <= Available
    for (i = 0; i < m; i++)
    {
        if (request[i] > avail[i])
        {
            printf("\nResources not available. Process must wait.\n");
            return 0;
        }
    }

    // Tentatively allocate
    for (i = 0; i < m; i++)
    {
        avail[i] -= request[i];
        alloc[reqProcess][i] += request[i];
        need[reqProcess][i] -= request[i];
    }

    // Check if safe after allocation
    if (!isSafe())
    {
        printf("\nRequest cannot be granted (unsafe state).\n");
    }
    else
    {
        printf("\nRequest can be granted safely.\n");
    }

    return 0;
}

/*
Output:
Enter number of processes: 5
Enter number of resources: 3

Enter Allocation Matrix:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

Enter Max Matrix:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

Enter Available Resources:
3 3 2

Need Matrix:
7 4 3 
1 2 2 
6 0 0 
0 1 1 
4 3 1 

System is in a SAFE state.
Safe Sequence: P1 -> P3 -> P4 -> P0 -> P2

Enter the process number making a request (0-4): 1
Enter request for each resource: 1 0 2

System is in a SAFE state.
Safe Sequence: P1 -> P3 -> P4 -> P0 -> P2

Request can be granted safely.
*/