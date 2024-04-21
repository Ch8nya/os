
//First fit
#include <iostream>

using namespace std;

class Ass6FirstFit {
public:
    static void firstFit(int blockSize[], int m, int processSize[], int n) {
        int allocation[n];
        for (int i = 0; i < n; i++) {
            allocation[i] = -1;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (blockSize[j] >= processSize[i]) {
                    allocation[i] = j;
                    blockSize[j] -= processSize[i];
                    break;
                }
            }
        }

        cout << "\nProcess No.\tProcess Size\tBlock no." << endl;
        for (int i = 0; i < n; i++) {
            cout << " " << (i + 1) << "\t\t" << processSize[i] << "\t\t";
            if (allocation[i] != -1)
                cout << allocation[i] + 1;
            else
                cout << "Not Allocated";
            cout << endl;
        }
    }
};

int main() {
    int m;
    cout << "Enter the number of memory blocks: ";
    cin >> m;

    int blockSize[m];
    cout << "Enter the sizes of memory blocks:" << endl;
    for (int i = 0; i < m; i++) {
        cin >> blockSize[i];
    }

    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int processSize[n];
    cout << "Enter the sizes of processes:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> processSize[i];
    }

    Ass6FirstFit::firstFit(blockSize, m, processSize, n);

    return 0;
}





//Next Fit
#include <iostream>

using namespace std;

class Ass6NextFit {
public:
    static void nextFit(int blockSize[], int m, int processSize[], int n) {
        int allocation[n];
        for (int i = 0; i < n; i++) {
            allocation[i] = -1;
        }

        int j = 0;
        int t = m - 1;

        for (int i = 0; i < n; i++) {
            while (j < m) {
                if (blockSize[j] >= processSize[i]) {
                    allocation[i] = j;
                    blockSize[j] -= processSize[i];
                    t = (j - 1 + m) % m;
                    break;
                }
                if (t == j) {
                    t = (j - 1 + m) % m;
                    break;
                }
                j = (j + 1) % m;
            }
        }

        cout << "\nProcess No.\tProcess Size\tBlock no." << endl;
        for (int i = 0; i < n; i++) {
            cout << " " << (i + 1) << "\t\t\t\t" << processSize[i] << "\t\t\t\t";
            if (allocation[i] != -1) {
                cout << allocation[i] + 1;
            } else {
                cout << "Not Allocated";
            }
            cout << endl;
        }
    }
};

int main() {
    int m;
    cout << "Enter the number of memory blocks: ";
    cin >> m;

    int blockSize[m];
    cout << "Enter the sizes of memory blocks:" << endl;
    for (int i = 0; i < m; i++) {
        cin >> blockSize[i];
    }

    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int processSize[n];
    cout << "Enter the sizes of processes:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> processSize[i];
    }

    Ass6NextFit::nextFit(blockSize, m, processSize, n);

    return 0;
}


