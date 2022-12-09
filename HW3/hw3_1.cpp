#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct process {
    int pid = 0;
    int arrivalTime = 0;
    int burstTime = 0;
    int remainTime = 0;
    int waitTime = 0;
    int turnAroundTime = 0;
    bool finished = false;
};

// sort by PID
bool byPID (const process &A, const process &B) {
    return A.pid <= B.pid;
}

// sort by remain time
bool byRemain (const process &A, const process &B) {
    if (A.remainTime == B.remainTime)
        return A.arrivalTime <= B.arrivalTime;
    return A.remainTime <= B.remainTime;
}

int main() {

    // get the number of processes
    int n; cin >> n; 
    // get the pid & arrival & burst time of each process
    vector <process> list(n);
    for (int i = 0; i < n; i++) {
        list[i].pid = i;
        cin >> list[i].arrivalTime;
    }
    for (int i = 0; i < n; i++) {
        cin >> list[i].burstTime;
        list[i].remainTime = list[i].burstTime;
    }

    int current_time = 0;
    int finished_count = 0;
    while (finished_count < n) {
        sort(list.begin(), list.end(), byRemain);
        for (int i = 0; i < n; i++) {
            if (list[i].arrivalTime <= current_time && list[i].finished != true) {
                list[i].remainTime -= 1;
                if (list[i].remainTime == 0) {
                    list[i].finished = true;
                    list[i].turnAroundTime = current_time + 1 - list[i].arrivalTime;
                    list[i].waitTime = list[i].turnAroundTime - list[i].burstTime;
                    finished_count += 1;
                }
                break;
            }
        }
        current_time += 1;
    }

    sort(list.begin(), list.end(), byPID);
    int total_waiting = 0, total_turnaround = 0;
    for (int i = 0; i < n; i++) {
        total_waiting += list[i].waitTime;
        total_turnaround += list[i].turnAroundTime;
        cout << list[i].waitTime << " " << list[i].turnAroundTime << "\n";
    }
    cout << total_waiting << "\n" << total_turnaround;

    return 0;
}