#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    int maxMat[n][m], avail[m];

    cout << "Enter Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maxMat[i][j];

    cout << "Enter Available Resources:\n";
    for (int i = 0; i < m; i++)
        cin >> avail[i];

    cout << "\n--- Deadlock Prevention Simulation ---\n";

    for (int i = 0; i < n; i++) {
        cout << "\nProcess P" << i << " requesting all resources at once...\n";
        bool canAllocate = true;
        for (int j = 0; j < m; j++) {
            if (maxMat[i][j] > avail[j]) {
                canAllocate = false;
                break;
            }
        }
        if (canAllocate) {
            cout << "Resources allocated to P" << i << ".\n";
            for (int j = 0; j < m; j++)
                avail[j] -= maxMat[i][j];

            cout << "Process P" << i << " finished and released resources.\n";
            for (int j = 0; j < m; j++)
                avail[j] += maxMat[i][j];
        } else {
            cout << "Process P" << i << " must wait (cannot hold some and wait for others).\n";
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