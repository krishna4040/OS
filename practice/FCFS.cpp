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

// Function to perform FCFS scheduling
void fcfsScheduling(Process processes[], int n)
{
    queue<Process> readyQueue;   // Queue to store processes ready for execution
    int currentTime = 0;         // Current time
    int totalTurnaroundTime = 0; // Total turnaround time of all processes
    int totalWaitingTime = 0;    // Total waiting time of all processes

    // Loop through each process
    for (int i = 0; i < n; i++)
    {
        // Move the current time to the arrival time of the process if it arrives later than the current time
        if (currentTime < processes[i].arrivalTime)
        {
            currentTime = processes[i].arrivalTime;
        }

        // Calculate waiting time for the current process
        int waitingTime = currentTime - processes[i].arrivalTime;
        totalWaitingTime += waitingTime;

        // Calculate turnaround time for the current process
        int turnaroundTime = waitingTime + processes[i].burstTime;
        totalTurnaroundTime += turnaroundTime;

        // Move the current time forward by the burst time of the current process
        currentTime += processes[i].burstTime;
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

    // Call the FCFS scheduling function
    fcfsScheduling(processes, n);

    return 0;
}
