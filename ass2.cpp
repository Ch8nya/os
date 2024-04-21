//FCFS
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    cout << "Enter the number of Processes: ";
    int n;
    cin >> n;

    int p[n], at[n], bt[n], ct[n], tat[n], wt[n];
    double avgTAT = 0.0, avgWT = 0.0;

    for (int i = 0; i < n; i++) {
        p[i] = i + 1; // Process numbers start from 1
    }

    for (int i = 0; i < n; i++) {
        cout << "Enter Process " << p[i] << " Arrival Time: ";
        cin >> at[i];
    }

    for (int i = 0; i < n; i++) {
        cout << "Enter Process " << p[i] << " Burst Time: ";
        cin >> bt[i];
    }

    // Sort processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                // Swap the processes if they are out of order
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(p[j], p[j + 1]);
            }
        }
    }

    // Calculate completion time, turnaround time, and waiting time
    ct[0] = at[0] + bt[0];
    tat[0] = ct[0] - at[0];
    wt[0] = tat[0] - bt[0];

    for (int i = 1; i < n; i++) {
        ct[i] = ct[i - 1] + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // Calculate average turnaround time and average waiting time
    for (int i = 0; i < n; i++) {
        avgTAT += tat[i];
        avgWT += wt[i];
    }

    avgTAT /= n;
    avgWT /= n;

    // Display results
    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << p[i] << "\t" << at[i] << "\t\t" << bt[i] << "\t\t" << ct[i] << "\t\t" << tat[i] << "\t\t" << wt[i] << endl;
    }

    // Display average turnaround time and average waiting time
    cout << "\nAverage Turnaround Time: " << avgTAT << endl;
    cout << "Average Waiting Time: " << avgWT << endl;

    return 0;
}

//SJF
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cout << "Enter no of process: ";
    cin >> n;

    vector<int> pid(n), at(n), bt(n), ct(n), ta(n), wt(n), f(n, 0);
    int st = 0, tot = 0;
    float avgwt = 0, avgta = 0;

    for (int i = 0; i < n; i++) {
        cout << "Enter process " << (i + 1) << " arrival time: ";
        cin >> at[i];
        cout << "Enter process " << (i + 1) << " burst time: ";
        cin >> bt[i];
        pid[i] = i + 1;
    }

    while (true) {
        int c = n, min = 999;

        if (tot == n)
            break;

        for (int i = 0; i < n; i++) {
            if ((at[i] <= st) && (f[i] == 0) && (bt[i] < min)) {
                min = bt[i];
                c = i;
            }
        }

        if (c == n)
            st++;
        else {
            ct[c] = st + bt[c];
            st += bt[c];
            ta[c] = ct[c] - at[c];
            wt[c] = ta[c] - bt[c];
            f[c] = 1;
            tot++;
        }
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";

    for (int i = 0; i < n; i++) {
        avgwt += wt[i];
        avgta += ta[i];
        cout << pid[i] << "\t" << at[i] << "\t\t" << bt[i] << "\t\t" << ct[i] << "\t\t" << ta[i] << "\t\t" << wt[i] << "\n";
    }

    cout << "\nAverage Turnaround Time: " << (avgta / n) << "\n";
    cout << "Average Waiting Time: " << (avgwt / n) << "\n";

    return 0;
}