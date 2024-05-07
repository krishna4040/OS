#include <iostream>
#include <queue>

using namespace std;

// Structure to represent a process
struct Process
{
    int id;          // Process ID
    int arrivalTime; // Arrival time of the process
    int burstTime;   // Burst time of the process
};

// Function to perform Round Robin scheduling
void roundRobinScheduling(Process processes[], int n, int quantum)
{
    queue<Process> readyQueue;   // Queue to store processes ready for execution
    int remainingBurstTime[n];   // Array to store remaining burst time for each process
    int currentTime = 0;         // Current time
    int totalTurnaroundTime = 0; // Total turnaround time of all processes
    int totalWaitingTime = 0;    // Total waiting time of all processes

    // Initialize remaining burst time for each process
    for (int i = 0; i < n; i++)
    {
        remainingBurstTime[i] = processes[i].burstTime;
    }

    int currentIndex = 0; // Index to keep track of current process in the processes array
    // Loop until all processes are executed
    while (!readyQueue.empty() || currentIndex < n)
    {
        // Add processes arriving at the current time to the ready queue
        while (currentIndex < n && processes[currentIndex].arrivalTime <= currentTime)
        {
            readyQueue.push(processes[currentIndex]);
            currentIndex++;
        }

        // If no process is ready to execute, move to the next arrival time
        if (readyQueue.empty())
        {
            currentTime = processes[currentIndex].arrivalTime;
            continue;
        }

        // Get the next process from the ready queue
        Process currentProcess = readyQueue.front();
        readyQueue.pop();

        // Execute the process for a time quantum or its remaining burst time, whichever is smaller
        int executionTime = min(quantum, remainingBurstTime[currentProcess.id]);
        remainingBurstTime[currentProcess.id] -= executionTime;
        currentTime += executionTime;

        // If the process still has remaining burst time, add it back to the ready queue
        if (remainingBurstTime[currentProcess.id] > 0)
        {
            readyQueue.push(currentProcess);
        }
        else
        {
            // Calculate turnaround time and waiting time for the completed process
            int turnaroundTime = currentTime - currentProcess.arrivalTime;
            int waitingTime = turnaroundTime - currentProcess.burstTime;
            totalTurnaroundTime += turnaroundTime;
            totalWaitingTime += waitingTime;
        }
    }

    // Calculate and print average turnaround time and average waiting time
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << endl;
    cout << "Average Waiting Time: " << (float)totalWaitingTime / n << endl;
}

// Main function
int main()
{
    // Prompt the user to enter the number of processes
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    // Array to store processes
    Process processes[n];
    // Prompt the user to enter arrival time and burst time for each process
    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i;
        cout << "Process " << i << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    // Prompt the user to enter time quantum for Round Robin scheduling
    int quantum;
    cout << "Enter time quantum: ";
    cin >> quantum;

    // Call the Round Robin scheduling function
    roundRobinScheduling(processes, n, quantum);

    return 0;
}
