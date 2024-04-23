#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Process structure
struct Process {
    int id;           // Process ID
    int arrivalTime;  // Arrival time
    int burstTime;    // Burst time
    int priority;     // Priority
    int remainingTime; // Remaining time for the process
};

// Function to implement FCFS scheduling algorithm
void FCFS(vector<Process> &processes) {
    int currentTime = 0;
    int n = processes.size();
    vector<int> completionTime(n);
    vector<int> turnAroundTime(n);
    vector<int> waitingTime(n);

    cout << "FCFS Scheduling\n";
    cout << "Process Execution Order: ";
    for (auto &process : processes) {
        if (currentTime < process.arrivalTime)
            currentTime = process.arrivalTime;
        cout << process.id << " ";
        completionTime[process.id - 1] = currentTime + process.burstTime;
        turnAroundTime[process.id - 1] = completionTime[process.id - 1] - process.arrivalTime;
        waitingTime[process.id - 1] = turnAroundTime[process.id - 1] - process.burstTime;
        currentTime += process.burstTime;
    }
    cout << endl;

    // Print completion time, turnaround time, and waiting time for each process
    cout << "Process\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << completionTime[i] << "\t\t" 
             << turnAroundTime[i] << "\t\t" << waitingTime[i] << endl;
    }
    cout << endl;
}

// Function to implement SJF scheduling algorithm
void SJF(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.burstTime < b.burstTime;
    });

    int currentTime = 0;
    int n = processes.size();
    vector<int> completionTime(n);
    vector<int> turnAroundTime(n);
    vector<int> waitingTime(n);

    cout << "SJF Scheduling\n";
    cout << "Process Execution Order: ";
    for (auto &process : processes) {
        if (currentTime < process.arrivalTime)
            currentTime = process.arrivalTime;
        cout << process.id << " ";
        completionTime[process.id - 1] = currentTime + process.burstTime;
        turnAroundTime[process.id - 1] = completionTime[process.id - 1] - process.arrivalTime;
        waitingTime[process.id - 1] = turnAroundTime[process.id - 1] - process.burstTime;
        currentTime += process.burstTime;
    }
    cout << endl;

    // Print completion time, turnaround time, and waiting time for each process
    cout << "Process\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << completionTime[i] << "\t\t" 
             << turnAroundTime[i] << "\t\t" << waitingTime[i] << endl;
    }
    cout << endl;
}

// Function to implement Round Robin scheduling algorithm
void RoundRobin(vector<Process> &processes, int quantum) {
    cout << "Round Robin Scheduling (Quantum: " << quantum << ")\n";
    cout << "Process Execution Order: ";

    int n = processes.size();
    vector<int> remainingTime(n);
    vector<int> completionTime(n);
    vector<int> turnAroundTime(n);
    vector<int> waitingTime(n);

    for (int i = 0; i < n; i++)
        remainingTime[i] = processes[i].burstTime;

    int currentTime = 0;
    while (true) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                done = false;
                if (remainingTime[i] > quantum) {
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                    cout << processes[i].id << " ";
                } else {
                    currentTime += remainingTime[i];
                    remainingTime[i] = 0;
                    cout << processes[i].id << " ";
                    completionTime[processes[i].id - 1] = currentTime;
                    turnAroundTime[processes[i].id - 1] = completionTime[processes[i].id - 1] - processes[i].arrivalTime;
                    waitingTime[processes[i].id - 1] = turnAroundTime[processes[i].id - 1] - processes[i].burstTime;
                }
            }
        }
        if (done) break;
    }
    cout << endl;

    // Print completion time, turnaround time, and waiting time for each process
    cout << "Process\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << completionTime[i] << "\t\t" 
             << turnAroundTime[i] << "\t\t" << waitingTime[i] << endl;
    }
    cout << endl;
}

// Function to implement Priority scheduling algorithm
void Priority(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.priority < b.priority;
    });

    int currentTime = 0;
    int n = processes.size();
    vector<int> completionTime(n);
    vector<int> turnAroundTime(n);
    vector<int> waitingTime(n);

    cout << "Priority Scheduling\n";
    cout << "Process Execution Order: ";
    for (auto &process : processes) {
        if (currentTime < process.arrivalTime)
            currentTime = process.arrivalTime;
        cout << process.id << " ";
        completionTime[process.id - 1] = currentTime + process.burstTime;
        turnAroundTime[process.id - 1] = completionTime[process.id - 1] - process.arrivalTime;
        waitingTime[process.id - 1] = turnAroundTime[process.id - 1] - process.burstTime;
        currentTime += process.burstTime;
    }
    cout << endl;

    // Print completion time, turnaround time, and waiting time for each process
    cout << "Process\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << completionTime[i] << "\t\t" 
             << turnAroundTime[i] << "\t\t" << waitingTime[i] << endl;
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter Arrival Time, Burst Time and Priority for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Process " << processes[i].id << ":\n";
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
        cout << "Priority: ";
        cin >> processes[i].priority;
        processes[i].remainingTime = processes[i].burstTime;
    }

    FCFS(processes);
    SJF(processes);
    
    int quantum;
    cout << "Enter Time Quantum for Round Robin Scheduling: ";
    cin >> quantum;
    RoundRobin(processes, quantum);
    
    Priority(processes);

    return 0;
}
