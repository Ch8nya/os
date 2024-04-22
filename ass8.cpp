//FCFS
#include <iostream>
#include <cstdlib>

using namespace std;

void FCFS(int arr[], int size, int head) {
    int seek_count = 0;
    int distance, cur_track;

    for (int i = 0; i < size; i++) {
        cur_track = arr[i];

        // calculate absolute distance
        distance = abs(cur_track - head);

        // increase the total count
        seek_count += distance;

        // accessed track is now new head
        head = cur_track;
    }

    cout << "Total number of seek operations = " << seek_count << endl;

    // Seek sequence would be the same as request array sequence
    cout << "Seek Sequence is" << endl;

    for (int i = 0; i < size; i++) {
        cout << arr[i] << endl;
    }
}

// Driver code
int main() {
    int size;
    cout << "Enter the number of disk requests: ";
    cin >> size;

    int arr[size];
    cout << "Enter the disk requests (separated by space): " << endl;
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    int head;
    cout << "Enter the initial head position: ";
    cin >> head;

    FCFS(arr, size, head);

    return 0;
}


//SSTF
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

// Calculates difference of each track number with the head position
void calculateDifference(int queue[], int head, int diff[], bool accessed[], int size) {
    for (int i = 0; i < size; i++)
        diff[i] = abs(queue[i] - head);
}

// find unaccessed track which is at minimum distance from head
int findMin(int diff[], bool accessed[], int size) {
    int index = -1;
    int minimum = INT_MAX;

    for (int i = 0; i < size; i++) {
        if (!accessed[i] && minimum > diff[i]) {
            minimum = diff[i];
            index = i;
        }
    }
    return index;
}

void shortestSeekTimeFirst(int request[], int head, int size) {
    if (size == 0)
        return;

    int diff[size]; // array to store distance of each track from head
  bool *accessed = new bool[size](); // value-initialize to false
// initialize all tracks as unaccessed

    int seek_count = 0; // count total number of seek operations
    int seek_sequence[size + 1]; // stores sequence in which disk access is done

    for (int i = 0; i < size; i++) {
        seek_sequence[i] = head;
        calculateDifference(request, head, diff, accessed, size);

        int index = findMin(diff, accessed, size);

        accessed[index] = true; // mark the track as accessed

        seek_count += diff[index]; // increase the total count

        head = request[index]; // accessed track is now new head
    }

    seek_sequence[size] = head; // for last accessed track

    cout << "Total number of seek operations = " << seek_count << endl;
    cout << "Seek Sequence is" << endl;

    for (int i = 0; i <= size; i++)
        cout << seek_sequence[i] << endl;
}

int main() {
    int n;
    cout << "Enter the number of disk requests: ";
    cin >> n;

    int arr[n];
    cout << "Enter the disk requests (separated by space): " << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int head;
    cout << "Enter the initial head position: ";
    cin >> head;

    shortestSeekTimeFirst(arr, head, n);

    return 0;
}




// SCAN
 #include<bits/stdc++.h>
using namespace std;
void SCAN(int arr[],int head,string direction,int size, int disksize){
  int seekcount =0;
  int distance, cur_track;
  vector<int> left,right;
  vector<int> seeksequence;
  if(direction=="left")left.push_back(0);
  else if(direction=="right")right.push_back(disksize-1);

  for(int i=0;i<size;i++){
    if(arr[i]<head)left.push_back(arr[i]);
    if(arr[i]>head)right.push_back(arr[i]);
  }
  sort(left.begin(),left.end());
  sort(right.begin(),right.end());

  int run=2;
  while(run--){
    if(direction=="left"){
      for(int i=left.size()-1;i>=0;i--){
        cur_track=left[i];
        seeksequence.push_back(cur_track);
        distance=abs(cur_track-head);
        seekcount+=distance;
        head=cur_track;
      }
      direction="right";
    }
    else if(direction=="right"){
      for(int i=0;i<right.size();i++){
        cur_track=right[i];
        seeksequence.push_back(cur_track);
        distance=abs(cur_track-head);
        seekcount+=distance;
        head=cur_track;
      }
      direction="left";
    }
  }
  cout<<"Total number of seek operations = "<<seekcount<<"\n";
  cout<<"Seek Sequence is: ";
  for(int i=0;i<seeksequence.size();i++){
    if(i==seeksequence.size()-1) cout<<seeksequence[i];
    else cout<<seeksequence[i]<<"->";
  }
  
  
}
int main(){
  int size =7;
  int disksize=200;
  int arr[7]={16,24,43,82,140,170,190};
  int head = 50;
  string direction="right";
  SCAN(arr,head,direction,size,disksize);
  return 0;
}

// C Scan
#include<bits/stdc++.h>
using namespace std;
void CSCAN(int arr[],int head,int size, int disksize){
  int seekcount=0;
  int distance,curtrack;
  vector<int> left,right;
  vector<int> seeksequence;

  left.push_back(0);
  right.push_back(disksize-1);

  for(int i=0;i<size;i++){
    if(arr[i]<head) left.push_back(arr[i]);
    else if(arr[i]>head) right.push_back(arr[i]);
  }
  sort(left.begin(),left.end());
  sort(right.begin(),right.end());

  for(int i=0;i<right.size();i++){
    curtrack=right[i];
    seeksequence.push_back(curtrack);
    distance=abs(curtrack-head);
    seekcount+=distance;
    head=curtrack;
  }
  head=0;
  seekcount+=(disksize-1);
  for(int i=0;i<left.size();i++){
    curtrack=left[i];
    seeksequence.push_back(curtrack);
    distance=abs(curtrack-head);
    seekcount+=distance;
    head=curtrack;
  }
  cout<<"Total number of seek operations: "<<seekcount<<"\n";
  cout<<"Seek Sequence is: "<<endl;
  for(int i=0;i<seeksequence.size();i++){
    if(i==seeksequence.size()-1) cout<<seeksequence[i]<<" ";
    else cout<<seeksequence[i]<<"->";
  }
}
int main(){
  int size=8;
  int disksize=200;
  int arr[8] = {16,24,43,82,140,170,190,199};
  int head=50;
  cout<<"Initial position of head: "<<head<<endl;
  CSCAN(arr,head,size,disksize);
  return 0;
}
