#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class BankersAlgorithm {
private:
    int n; // number of processes
    int available[3]; // Available instances of resources A, B, and C
    int maximum[100][3]; // Maximum demand of each process for A, B, and C
    int allocation[100][3]; // Resources currently allocated to each process for A, B, and C
    int need[100][3]; // Remaining need of each process for A, B, and C

public:
    BankersAlgorithm(int n) {
        this->n = n;
    }

    void initializeValues() {
        // Read available resources
        cout << "Enter the available instances of resources (A B C): ";
        for (int i = 0; i < 3; i++) {
            cin >> available[i];
        }

        // Read maximum demand of each process
        for (int i = 0; i < n; i++) {
            cout << "Enter the maximum demand of process " << i << " (A B C): ";
            for (int j = 0; j < 3; j++) {
                cin >> maximum[i][j];
            }
        }

        // Read allocated resources for each process
        for (int i = 0; i < n; i++) {
            cout << "Enter the allocated resources for process " << i << " (A B C): ";
            for (int j = 0; j < 3; j++) {
                cin >> allocation[i][j];
                need[i][j] = maximum[i][j] - allocation[i][j];
            }
        }
    }

    void getSafeSequence() {
        int work[3];
        for (int i = 0; i < 3; i++) {
            work[i] = available[i];
        }

        bool finish[100] = {false};
        queue<int> safeSequence;

        while (true) {
            bool found = false;
            for (int i = 0; i < n; i++) {
                if (!finish[i]) {
                    bool canAllocate = true;
                    for (int j = 0; j < 3; j++) {
                        if (need[i][j] > work[j]) {
                            canAllocate = false;
                            break;
                        }
                    }
                    if (canAllocate) {
                        for (int j = 0; j < 3; j++) {
                            work[j] += allocation[i][j];
                        }
                        finish[i] = true;
                        safeSequence.push(i);
                        found = true;
                    }
                }
            }
            if (!found) {
                break;
            }
        }

        if (safeSequence.size() == n) {
            cout << "The system is in a safe state. Safe sequence is: ";
            while (!safeSequence.empty()) {
                cout << safeSequence.front() << " ";
                safeSequence.pop();
            }
            cout << endl;
        } else {
            cout << "The system is in an unsafe state and cannot reach a safe state." << endl;
        }
    }
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    BankersAlgorithm bankersAlgorithm(n);
    bankersAlgorithm.initializeValues();

    bankersAlgorithm.getSafeSequence();

    return 0;
}