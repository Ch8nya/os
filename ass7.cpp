//FCFS
#include <iostream>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <string>
using namespace std;

// Method to find page faults using FIFO
int pageFaults(int pages[], int n, int capacity) 
{
    unordered_set<int> s;
    queue<int> indexes;
    int page_faults = 0;

    for (int i = 0; i < n; i++)
    {
        if (s.size() < capacity)
        {
            if (s.find(pages[i]) == s.end())
            {
                s.insert(pages[i]);
                page_faults++;
                indexes.push(pages[i]);
            }
        }
        else
        {
            if (s.find(pages[i]) == s.end())
            {
                int val = indexes.front();
                indexes.pop();
                s.erase(val);
                s.insert(pages[i]);
                indexes.push(pages[i]);
                page_faults++;
            }
        }
    }

    return page_faults;
}

// Driver method
int main()
{
    int capacity;
    cout << "Enter the capacity: ";
    cin >> capacity;
    cin.ignore(); // Ignore the newline character after capacity input

    string input;
    cout << "Enter the pages (separated by space): ";
    getline(cin, input);

    // Parse the input string to get the page numbers
    istringstream iss(input);
    int pages[100];
    int n = 0;
    int page;
    while (iss >> page)
    {
        pages[n++] = page;
    }

    cout << "Page Faults: " << pageFaults(pages, n, capacity) << endl;

    return 0;
}

//LRU

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

// Method to find page faults using indexes
int pageFaults(int pages[], int n, int capacity)
{
    unordered_set<int> s;
    unordered_map<int, int> indexes;
    int page_faults = 0;

    for (int i = 0; i < n; i++)
    {
        if (s.size() < capacity)
        {
            if (s.find(pages[i]) == s.end())
            {
                s.insert(pages[i]);
                page_faults++;
            }
            indexes[pages[i]] = i;
        }
        else
        {
            if (s.find(pages[i]) == s.end())
            {
                int lru = INT_MAX, val = INT_MIN;
                for (auto it = s.begin(); it != s.end(); it++)
                {
                    int temp = *it;
                    if (indexes[temp] < lru)
                    {
                        lru = indexes[temp];
                        val = temp;
                    }
                }
                s.erase(val);
                indexes.erase(val);
                s.insert(pages[i]);
                page_faults++;
            }
            indexes[pages[i]] = i;
        }
    }

    return page_faults;
}

// Driver method
int main()
{
    int capacity;
    cout << "Enter the capacity: ";
    cin >> capacity;
    cin.ignore(); // Ignore the newline character

    string input;
    cout << "Enter the pages (separated by space): ";
    getline(cin, input);

    // Parse the input string to get the page numbers
    istringstream iss(input);
    int pages[100];
    int n = 0;
    int page;
    while (iss >> page)
    {
        pages[n++] = page;
    }

    cout << "Page Faults: " << pageFaults(pages, n, capacity) << endl;

    return 0;
}

//Optimal
#include <iostream>
using namespace std;
int main() {
int flag1, flag2, flag3, i, j, k, position, max, faults = 0;
int num_frames = 4;
int frames[num_frames];
int temp[num_frames];
int inputStream[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
int num_pages = sizeof(inputStream) / sizeof(inputStream[0]);
for(i = 0; i < num_frames; i++) {

frames[i] = -1;
}
for(i = 0; i < num_pages; i++) {
flag1 = flag2 = 0;
for(j = 0; j < num_frames; j++) {
if(frames[j] == inputStream[i]) {
flag1 = flag2 = 1;
break;
}
}
if(flag1 == 0) {
for(j = 0; j < num_frames; j++) {
if(frames[j] == -1) {
faults++;
frames[j] = inputStream[i];
flag2 = 1;
break;
}
}
}
if(flag2 == 0) {
flag3 = 0;
for(j = 0; j < num_frames; j++) {
temp[j] = -1;
for(k = i + 1; k < num_pages; k++) {
if(frames[j] == inputStream[k]) {
temp[j] = k;
break;
}
}
}
for(j = 0; j < num_frames; j++) {
if(temp[j] == -1) {
position = j;
flag3 = 1;
break;
}
}
if(flag3 == 0) {
max = temp[0];
position = 0;

for(j = 1; j < num_frames; j++) {
if(temp[j] > max) {
max = temp[j];
position = j;
}
}
}
frames[position] = inputStream[i];
faults++;
}
cout << endl;
for(j = 0; j < num_frames; j++) {
cout << frames[j] << "\t";
}
}
cout << endl << endl;
cout << "Total Page Faults = " << faults << endl;
cout << "Total Hits = " << num_pages - faults << endl;
return 0;
}
