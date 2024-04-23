#include <bits/stdc++.h>
using namespace std;

int FIFO(vector<int> &requests, int head) {
    int totalMovement = 0;
    int current = head;
    for (int request : requests) {
        totalMovement += abs(request - current);
        current = request;
    }
    return totalMovement;
}

int SSTF(vector<int> &requests, int head) {
    int totalMovement = 0;
    vector<bool> visited(requests.size(), false);
    int current = head;
    for (int i = 0; i < requests.size(); i++) {
        int minDist = INT_MAX;
        int index = -1;
        for (int j = 0; j < requests.size(); j++) {
            if (!visited[j]) {
                int dist = abs(requests[j] - current);
                if (dist < minDist) {
                    minDist = dist;
                    index = j;
                }
            }
        }
        visited[index] = true;
        totalMovement += minDist;
        current = requests[index];
    }
    return totalMovement;
}

int SCAN(vector<int> &requests, int head, int maxCylinder) {
    int totalMovement = 0;
    vector<int> sortedRequests = requests;
    sortedRequests.push_back(head);
    sort(sortedRequests.begin(), sortedRequests.end());
    int index = 0;
    for (int i = 0; i < sortedRequests.size(); i++) {
        if (sortedRequests[i] == head) {
            index = i;
            break;
        }
    }
    totalMovement += sortedRequests[index];
    for (int i = index; i >= 0; i--)
        totalMovement += abs(sortedRequests[i] - sortedRequests[i - 1]);
    totalMovement += maxCylinder - sortedRequests[0];
    for (int i = 1; i <= index; i++)
        totalMovement += abs(sortedRequests[i] - sortedRequests[i - 1]);
    return totalMovement;
}

int CSCAN(vector<int> &requests, int head, int maxCylinder) {
    int totalMovement = 0;
    vector<int> sortedRequests = requests;
    sortedRequests.push_back(head);
    sort(sortedRequests.begin(), sortedRequests.end());
    int index = 0;
    for (int i = 0; i < sortedRequests.size(); i++) {
        if (sortedRequests[i] == head) {
            index = i;
            break;
        }
    }
    totalMovement += sortedRequests[index];
    for (int i = index; i >= 0; i--)
        totalMovement += abs(sortedRequests[i] - sortedRequests[i - 1]);
    totalMovement += maxCylinder - sortedRequests[index + 1];
    totalMovement += sortedRequests[0];
    for (int i = 1; i <= index; i++)
        totalMovement += abs(sortedRequests[i] - sortedRequests[i - 1]);
    return totalMovement;
}

int main() {
    int n, head, maxCylinder;
    cout << "Enter number of requests: ";
    cin >> n;
    vector<int> requests(n);
    cout << "Enter requests: ";
    for (int i = 0; i < n; i++)
        cin >> requests[i];
    cout << "Enter head position: ";
    cin >> head;
    cout << "Enter maximum cylinder: ";
    cin >> maxCylinder;

    cout << "\nFIFO Disk Scheduling Algorithm:\n";
    cout << "Total movement: " << FIFO(requests, head) << endl;

    cout << "\nSSTF Disk Scheduling Algorithm:\n";
    cout << "Total movement: " << SSTF(requests, head) << endl;

    cout << "\nSCAN Disk Scheduling Algorithm:\n";
    cout << "Total movement: " << SCAN(requests, head, maxCylinder) << endl;

    cout << "\nC-SCAN Disk Scheduling Algorithm:\n";
    cout << "Total movement: " << CSCAN(requests, head, maxCylinder) << endl;

    return 0;
}