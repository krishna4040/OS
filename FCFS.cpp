#include "bits/stdc++.h"
using namespace std;

struct process
{
    string processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
};

bool arrivalTimeSort(process a, process b)
{
    return a.arrivalTime < b.arrivalTime;
}

void fsScheduling(vector<process> &processes)
{
    sort(processes.begin(), processes.end(), arrivalTimeSort);
    for (int i = 0; i < processes.size(); i++)
    {
        process *currProcess = &processes[i];

        if (i == 0)
            currProcess->completionTime = currProcess->arrivalTime + currProcess->burstTime;
        else
            currProcess->completionTime = max(currProcess->arrivalTime, processes[i - 1].completionTime) + currProcess->burstTime;
        currProcess->turnAroundTime = currProcess->completionTime - currProcess->arrivalTime;
        currProcess->waitingTime = currProcess->turnAroundTime - currProcess->burstTime;
    }
}

void displayResult(vector<process> &processes)
{
    for (int i = 0; i < processes.size(); i++)
    {
        process *curr = &processes[i];
        cout << "process: " << curr->processID << endl;
        cout << "AT: " << curr->arrivalTime << endl;
        cout << "BT: " << curr->burstTime << endl;
        cout << "CT: " << curr->completionTime << endl;
        cout << "TAT: " << curr->turnAroundTime << endl;
        cout << "WT: " << curr->waitingTime << endl;
    }
}

int main(int argc, char const *argv[])
{
    int n;
    cout << "Enter Number of processes: ";
    cin >> n;

    vector<process> processes(n);
    for (int i = 0; i < n; i++)
    {
        process *p = new process();

        cout << "Enter Process Id: ";
        cin >> p->processID;

        cout << "Enter AT: ";
        cin >> p->arrivalTime;

        cout << "Enter BT: ";
        cin >> p->burstTime;

        processes.push_back(*p);
    }

    fsScheduling(processes);
    displayResult(processes);

    return 0;
}