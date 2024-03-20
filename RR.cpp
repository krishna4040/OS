#include "bits/stdc++.h"
using namespace std;

class Node
{
public:
    string data;
    Node *next;
    Node(string value) : data(value), next(nullptr) {}
};

class Queue
{
private:
    Node *front;
    Node *rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    bool isEmpty()
    {
        return front == nullptr;
    }

    void enqueue(string pid)
    {
        Node *newNode = new Node(pid);
        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    string dequeue()
    {
        if (isEmpty())
        {
            std::cerr << "Queue is empty" << std::endl;
            return nullptr;
        }

        string value = front->data;
        Node *temp = front;

        if (front == rear)
        {
            front = rear = nullptr;
        }
        else
        {
            front = front->next;
        }
        delete temp;
        return value;
    }

    string peek()
    {
        if (isEmpty())
        {
            std::cerr << "Queue is empty" << std::endl;
            return nullptr;
        }

        return front->data;
    }

    void display()
    {
        if (isEmpty())
        {
            std::cout << "Queue is empty" << std::endl;
            return;
        }

        Node *current = front;
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

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

process getProcess(string pid, vector<process> &processes)
{
    for (auto &&p : processes)
        if (p.processID == pid)
            return p;
}

int getTAT(process p)
{
    return p.completionTime - p.arrivalTime;
}

int getWT(process p)
{
    return p.turnAroundTime - p.burstTime;
}

int computeTotalBurstTime(vector<process> &processes)
{
    int totalBurstTime = 0;
    for (auto &&p : processes)
        totalBurstTime += p.burstTime;
    return totalBurstTime;
}

void displayProccess(vector<process> &processes)
{
    for (auto &&p : processes)
    {
        cout << "PID: " << p.processID << endl;
        cout << "CompletionTime: " << p.completionTime << endl;
        cout << "TurnAround Time: " << p.turnAroundTime << endl;
        cout << "Waiting Time: " << p.waitingTime << endl;
    }
}

void RoundRobinScheduling(vector<process> &processes, int timeQuantum)
{
    sort(processes.begin(), processes.end(), arrivalTimeSort);
    Queue *ready_queue = new Queue();
    Queue *running_queue = new Queue();

    int currProcessIdx = 0;
    int timeMeasure = 0;

    process firstProcess = processes[currProcessIdx];
    timeMeasure = firstProcess.arrivalTime;
    ready_queue->enqueue(firstProcess.processID);
    while (!ready_queue->isEmpty())
    {
        string current_readyProcess_pid = ready_queue->dequeue();

        cout << "CURRENT_PROCESS_ID--->" << current_readyProcess_pid;

        process currentProcess = getProcess(current_readyProcess_pid, processes);
        running_queue->enqueue(currentProcess.processID);
        if (!running_queue->isEmpty())
        {
            string running_process_pid = running_queue->dequeue();
            process running_process = getProcess(running_process_pid, processes);
            if (running_process.burstTime <= timeQuantum)
            {
                timeMeasure += running_process.burstTime;
                running_process.completionTime = timeMeasure;
                running_process.burstTime = 0;
            }
            else
            {
                running_process.burstTime -= timeQuantum;
                timeMeasure += timeQuantum;
            }
        }

        if (currProcessIdx < processes.size())
        {
            process nextProcess = processes[++currProcessIdx];
            if (nextProcess.arrivalTime >= timeMeasure)
                ready_queue->enqueue(nextProcess.processID);
        }
        else
        {
            currProcessIdx--;
            ready_queue->enqueue(currentProcess.processID);
        }
    }
}

int main(int argc, char const *argv[])
{
    int n;
    cout << "Enter Number of Processes: ";
    cin >> n;

    vector<process> processes(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Process ID: ";
        cin >> processes[i].processID;

        cout << "Enter Process Arrival time: ";
        cin >> processes[i].arrivalTime;

        cout << "Enter Burst time: ";
        cin >> processes[i].burstTime;
    }

    int timeQuantum;
    cout << "Enter Time Quantum: ";
    cin >> timeQuantum;

    cout << "-----------------" << endl;
    int totalBurstTime = computeTotalBurstTime(processes);
    cout << "Total burst time is: " << totalBurstTime << endl;

    RoundRobinScheduling(processes, timeQuantum);
    for (auto &&p : processes)
    {
        p.turnAroundTime = getTAT(p);
        p.waitingTime = getWT(p);
    }

    cout << "--------------------------" << endl;
    displayProccess(processes);

    return 0;
}