#include <bits/stdc++.h>
using namespace std;

int n, m; // Global for convenience
int alloc[20][20], maxMat[20][20], need[20][20], avail[20];

// Function to check safe state and print sequence
bool isSafe() {
    int work[20], finish[20], safeSeq[20];
    int count = 0;

    // Initialize work and finish
    for (int i = 0; i < m; i++)
        work[i] = avail[i];
    for (int i = 0; i < n; i++)
        finish[i] = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "\nSystem is NOT in a safe state.\n";
            return false; // Not safe
        }
    }

    cout << "\nSystem is in a SAFE state.\nSafe Sequence: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSeq[i];
        if (i != n - 1)
            cout << " -> ";
    }
    cout << "\n";
    return true; // Safe
}

int main() {
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "\nEnter Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maxMat[i][j];

    cout << "\nEnter Available Resources:\n";
    for (int i = 0; i < m; i++)
        cin >> avail[i];

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maxMat[i][j] - alloc[i][j];

    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << need[i][j] << " ";
        cout << "\n";
    }

    // Check initial safe state
    if (!isSafe()) {
        cout << "\nSystem is NOT in a safe state.\n";
        return 0;
    }

    // Resource request handling
    int reqProcess;
    cout << "\nEnter the process number making a request (0-" << n - 1 << "): ";
    cin >> reqProcess;

    int request[20];
    cout << "Enter request for each resource: ";
    for (int i = 0; i < m; i++)
        cin >> request[i];

    // Check 1: Request <= Need
    for (int i = 0; i < m; i++) {
        if (request[i] > need[reqProcess][i]) {
            cout << "\nError: Process has exceeded its maximum claim.\n";
            return 0;
        }
    }

    // Check 2: Request <= Available
    for (int i = 0; i < m; i++) {
        if (request[i] > avail[i]) {
            cout << "\nResources not available. Process must wait.\n";
            return 0;
        }
    }

    // Tentatively allocate
    for (int i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[reqProcess][i] += request[i];
        need[reqProcess][i] -= request[i];
    }

    // Check if safe after allocation
    if (!isSafe()) {
        cout << "\nRequest cannot be granted (unsafe state).\n";
    } else {
        cout << "\nRequest can be granted safely.\n";
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