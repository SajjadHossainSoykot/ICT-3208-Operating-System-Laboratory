#include <stdio.h>

int main()
{
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int max[n][m], alloc[n][m], avail[m];

    printf("Enter Max Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    printf("\n--- Deadlock Prevention Simulation ---\n");

    for (int i = 0; i < n; i++)
    {
        printf("\nProcess P%d requesting all resources at once...\n", i);
        int canAllocate = 1;
        for (int j = 0; j < m; j++)
        {
            if (max[i][j] > avail[j])
            {
                canAllocate = 0;
                break;
            }
        }
        if (canAllocate)
        {
            printf("Resources allocated to P%d.\n", i);
            for (int j = 0; j < m; j++)
                avail[j] -= max[i][j];
            printf("Process P%d finished and released resources.\n", i);
            for (int j = 0; j < m; j++)
                avail[j] += max[i][j];
        }
        else
        {
            printf("Process P%d must wait (cannot hold some and wait for others).\n", i);
        }
    }
    return 0;
}
/*
Output:
Enter number of processes: 3
Enter number of resources: 3
Enter Max Matrix:
7 5 3
3 2 2
9 0 2
Enter Available Resources:
3 3 2

--- Deadlock Prevention Simulation ---

Process P0 requesting all resources at once...
Process P0 must wait (cannot hold some and wait for others).

Process P1 requesting all resources at once...
Resources allocated to P1.
Process P1 finished and released resources.

Process P2 requesting all resources at once...
Process P2 must wait (cannot hold some and wait for others).
*/