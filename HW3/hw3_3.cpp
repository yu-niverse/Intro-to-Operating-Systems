#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct process {
    int pid = 0;
    int arrivalTime = 0;
    int burstTime = 0;
    int remainTime = 0;
    int waitTime = 0;
    int turnAroundTime = 0;
    bool waiting = false;
    bool finished = false;
};

// sort by PID
bool byPID (const process &A, const process &B) {
    return A.pid <= B.pid;
}

// sort by arrival time
bool byArrival (const process &A, const process &B) {
    if (A.arrivalTime == B.arrivalTime) 
        return A.pid < B.pid;
    return A.arrivalTime < B.arrivalTime;
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
    int time_quantum; cin >> time_quantum;

    sort(list.begin(), list.end(), byArrival);
    int current_time = 0;
    int finished_count = 0;
    int tmp_quantum = time_quantum;
    int previous = -1;
    bool not_finished = false;
    queue <int> queue0, queue1;

    while (finished_count < n) {
        for (int i = 0; i < n; i++) {
            if ((list[i].arrivalTime <= current_time && !list[i].finished) && !list[i].waiting) {
                list[i].waiting = true;
                queue0.push(i);
            }
        }
        
        current_time += 1;
        if (queue0.empty() && queue1.empty()) continue;

        if (queue0.empty()) {
            process *chosen = &list[queue1.front()];
            chosen->remainTime -= 1;

            if (chosen->remainTime == 0) {
                chosen->finished = true;
                chosen->turnAroundTime = current_time - chosen->arrivalTime;
                chosen->waitTime = chosen->turnAroundTime - chosen->burstTime;
                finished_count += 1;
                queue1.pop();
                not_finished = false;
            } else not_finished = true;

            previous = 1;
        }
        else {
            if (previous == 1 && not_finished) {
                queue1.push(queue1.front());
                queue1.pop();
            }

            process *chosen = &list[queue0.front()];
            chosen->remainTime -= 1;
            tmp_quantum -= 1;

            if (tmp_quantum == 0 && chosen->remainTime != 0) {
                queue1.push(queue0.front());
                queue0.pop();
                tmp_quantum = time_quantum;
            }

            if (chosen->remainTime == 0) {
                chosen->finished = true;
                chosen->turnAroundTime = current_time - chosen->arrivalTime;
                chosen->waitTime = chosen->turnAroundTime - chosen->burstTime;
                finished_count += 1;
                queue0.pop();
                chosen->waiting = false;
                tmp_quantum = time_quantum;
            }
            previous = 0;
        }
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