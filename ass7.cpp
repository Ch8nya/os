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