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


// Round Robin:
#include<stdio.h>
int main()
{
//Input no of processed
int n;
printf("Enter Total Number of Processes:");
scanf("%d", &n);
int wait_time = 0, ta_time = 0, arr_time[n], burst_time[n], temp_burst_time[n];
int x = n;
//Input details of processes
for(int i = 0; i < n; i++)
{
printf("Enter Details of Process %d \n", i + 1);
printf("Arrival Time: ");
scanf("%d", &arr_time[i]);
printf("Burst Time: ");
scanf("%d", &burst_time[i]);
temp_burst_time[i] = burst_time[i];
}
//Input time slot
int time_slot;
printf("Enter Time Quantum:");
scanf("%d", &time_slot);

//Total indicates total time
//counter indicates which process is executed
int total = 0, counter = 0,i;
printf("Process ID Burst Time Turnaround Time Waiting Time\n");
for(total=0, i = 0; x!=0; )
{
// define the conditions
if(temp_burst_time[i] <= time_slot && temp_burst_time[i] > 0)
{
total = total + temp_burst_time[i];
temp_burst_time[i] = 0;
counter=1;
}
else if(temp_burst_time[i] > 0)
{
temp_burst_time[i] = temp_burst_time[i] - time_slot;
total += time_slot;
}
if(temp_burst_time[i]==0 && counter==1)
{
x--; //decrement the process no.
printf("\nProcess No %d \t\t %d\t\t\t\t %d\t\t\t %d", i+1, burst_time[i],
total-arr_time[i], total-arr_time[i]-burst_time[i]);
wait_time = wait_time+total-arr_time[i]-burst_time[i];
ta_time += total -arr_time[i];
counter =0;
}
if(i==n-1)
{
i=0;
}
else if(arr_time[i+1]<=total)
{
i++;
}
else
{
i=0;
}
}

float average_wait_time = wait_time * 1.0 / n;
float average_turnaround_time = ta_time * 1.0 / n;
printf("\nAverage Waiting Time:%f", average_wait_time);
printf("\nAvg Turnaround Time:%f", average_turnaround_time);
return 0;
}

//Priority
#include<stdio.h>
// Structure to represent a process
struct Process {
int process_id; // Process ID
int priority; // Priority of the process
int burst_time; // Burst time of the process
};
// Function to swap two processes
void swap(struct Process *a, struct Process *b) {
struct Process temp = *a;
*a = *b;
*b = temp;

}
// Function to perform Priority Scheduling
void priorityScheduling(struct Process processes[], int n) {
// Sort the processes based on priority (higher priority first)
for (int i = 0; i < n - 1; i++) {
for (int j = 0; j < n - i - 1; j++) {
if (processes[j].priority > processes[j + 1].priority) {
swap(&processes[j], &processes[j + 1]);
}
}
}
// Variables to store waiting time and turnaround time
int waiting_time[n], turnaround_time[n];
// Calculate waiting time and turnaround time for each process
waiting_time[0] = 0;
turnaround_time[0] = processes[0].burst_time;
for (int i = 1; i < n; i++) {
waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
}
// Calculate total waiting time and turnaround time
double total_waiting_time = 0, total_turnaround_time = 0;
for (int i = 0; i < n; i++) {
total_waiting_time += waiting_time[i];
total_turnaround_time += turnaround_time[i];
}
// Print the details of each process
printf("Process ID\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
for (int i = 0; i < n; i++) {
printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].priority,
processes[i].burst_time, waiting_time[i], turnaround_time[i]);
}
// Print average waiting time and average turnaround time

printf("Average Waiting Time: %.2lf\n", total_waiting_time / n);
printf("Average Turnaround Time: %.2lf\n", total_turnaround_time / n);
}
int main() {
int n;
printf("Enter the number of processes: ");
scanf("%d", &n);
// Declare an array of processes
struct Process processes[n];
// Input details of each process
for (int i = 0; i < n; i++) {
printf("Enter details for Process %d:\n", i + 1);
printf("Process ID: ");
scanf("%d", &processes[i].process_id);
printf("Priority: ");
scanf("%d", &processes[i].priority);
printf("Burst Time: ");
scanf("%d", &processes[i].burst_time);
}
// Perform Priority Scheduling
priorityScheduling(processes, n);
return 0;
}
