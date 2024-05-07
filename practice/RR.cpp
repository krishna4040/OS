#include <iostream>
#include <queue>
using namespace std;

struct Process
{
    int id;
    int AT;
    int BT;
};

void RR(int TQ, Process P[], int n) {
    queue<Process> readyQueue;
    int currTime = 0;
    int remainingBT[n];
    int totalTAT = 0;
    int totalWT = 0;

    for (int i = 0; i < n; i++) {
        remainingBT[i] = P[i].BT;
    }
    
    int currIdx = 0;
    while (currIdx < n || !readyQueue.empty()) {
        while (currIdx < n && P[currIdx].AT <= currTime) {
            readyQueue.push(P[currIdx]);
            currIdx++;
        }
        if (readyQueue.empty()) {
            currTime = P[currIdx].AT;
            continue;
        }
        
        Process currProcess = readyQueue.front();
        readyQueue.pop();
        int execTime = min(TQ, currProcess.BT);
        remainingBT[currProcess.id] -= execTime;
        currTime += execTime;

        if (remainingBT[currProcess.id]) {
            readyQueue.push(currProcess);
        } else {
            int tat = currTime - currProcess.AT;
            int wt = tat - currProcess.BT;
            totalTAT += tat;
            totalWT += wt;
        }
    }
    
    cout << "Average Turnaround Time: " << (float)totalTAT / n << endl;
    cout << "Average Waiting Time: " << (float)totalWT / n << endl;
}

int main(int argc, char const *argv[])
{
    /* code */
    std::cout << "Hello World!" << std::endl;
    return 0;
}
