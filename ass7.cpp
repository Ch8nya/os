#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <unordered_map>

using namespace std;

// Function to simulate First Come First Serve (FCFS) paging algorithm
int FCFS(vector<int> &pages, int frameSize) {
    unordered_set<int> s; 
    queue<int> indexes; 
    int n = pages.size();
    int capacity = frameSize;

    int page_faults = 0; 
    for (int i=0; i<n; i++) {
        if (s.size() < capacity) { 
            if (s.find(pages[i])==s.end()) { 
                s.insert(pages[i]); 
                page_faults++; 
                indexes.push(pages[i]); 
            } 
        } else { 
            if (s.find(pages[i]) == s.end()) { 
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

// Function to simulate Least Recently Used (LRU) paging algorithm
int LRU(vector<int> &pages, int frameSize) {
    unordered_set<int> s; 
    unordered_map<int, int> indexes; 
    int n = pages.size();
    int capacity = frameSize;
  
    int page_faults = 0; 
    for (int i=0; i<n; i++) { 
        if (s.size() < capacity) { 
            if (s.find(pages[i])==s.end()) { 
                s.insert(pages[i]); 
                page_faults++; 
            } 
            indexes[pages[i]] = i; 
        } else { 
            if (s.find(pages[i]) == s.end()) { 
                int lru = INT_MAX, val; 
                for (auto it=s.begin(); it!=s.end(); it++) { 
                    if (indexes[*it] < lru) { 
                        lru = indexes[*it]; 
                        val = *it; 
                    } 
                } 
                s.erase(val); 
                s.insert(pages[i]); 
                page_faults++; 
            } 
            indexes[pages[i]] = i; 
        } 
    } 
  
    return page_faults;
}


int optimal(vector<int> &pg, int fn) {
    int pn = (int)pg.size();
    vector<int>fr(fn,-1);
    int hit = 0;
    for (int i = 0; i < pn; i++) {
        bool found = false;
        for (int j = 0; j < fn; j++) {
            if (fr[j] == pg[i]) {
                hit++;
                found = true;
                break;
            }
        }
 
        if (found)
            continue;
        bool emptyFrame = false;
        for (int j = 0; j < fn; j++) {
            if (fr[j] == -1) {
                fr[j] = pg[i];
                emptyFrame = true;
                break;
            }
        }
 
        if (emptyFrame)
            continue;

        int farthest = -1, replaceIndex = -1;
        for (int j = 0; j < fn; j++) {
            int k;
            for (k = i + 1; k < pn; k++) {
                if (fr[j] == pg[k]) {
                    if (k > farthest) {
                        farthest = k;
                        replaceIndex = j;
                    }
                    break;
                }
            }
            if (k == pn) {
                replaceIndex = j;
                break;
            }
        }
        fr[replaceIndex] = pg[i];
    }
    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
    return pn-hit;
}

int main() {
    int frameSize, n;
    cout << "Enter number of frames: ";
    cin >> frameSize;
    cout << "Enter number of pages: ";
    cin >> n;
    vector<int> pages(n);
    cout << "Enter page references: ";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "\nFCFS Page Replacement Algorithm:\n";
    cout << "Number of page faults: " << FCFS(pages, frameSize) << endl;

    cout << "\nLRU Page Replacement Algorithm:\n";
    cout << "Number of page faults: " << LRU(pages, frameSize) << endl;

    cout << "\nOptimal Page Replacement Algorithm:\n";
    cout << "Number of page faults: " << optimal(pages, frameSize) << endl;

    return 0;
}

/*
4
13
7 0 1 2 0 3 0 4 2 3 0 3 2
*/
