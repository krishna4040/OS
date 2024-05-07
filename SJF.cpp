#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a process
struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int start_time;  // Time when process starts execution
    int finish_time; // Time when process finishes execution

    // Constructor
    Process(int id, int arrival_time, int burst_time) : id(id), arrival_time(arrival_time), burst_time(burst_time), start_time(0), finish_time(0) {}

    // Comparison operator for sorting
    bool operator<(const Process &other) const
    {
        return burst_time < other.burst_time; // Shorter burst time has higher priority
    }
};

// Shortest Job First (SJF) Scheduling Algorithm
void shortestJobFirstScheduling(vector<Process> &processes)
{
    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.arrival_time < b.arrival_time; });

    int current_time = 0;

    for (auto &process : processes)
    {
        // Wait until process arrives if necessary
        if (process.arrival_time > current_time)
            current_time = process.arrival_time;

        // Record start time
        process.start_time = current_time;

        // Execute process
        cout << "Process " << process.id << " is running..." << endl;
        current_time += process.burst_time;

        // Record finish time
        process.finish_time = current_time;

        cout << "Process " << process.id << " completed!" << endl;
    }

    // Calculate turnaround time (TAT) and waiting time (WT) for each process
    for (const auto &process : processes)
    {
        int tat = process.finish_time - process.arrival_time;
        int wt = tat - process.burst_time;
        cout << "Process " << process.id << " TAT: " << tat << ", WT: " << wt << endl;
    }
}

int main()
{
    // Example processes
    vector<Process> processes = {
        Process(1, 0, 6),
        Process(2, 1, 4),
        Process(3, 2, 3),
        Process(4, 3, 5)};

    // Execute Shortest Job First (SJF) scheduling algorithm
    shortestJobFirstScheduling(processes);

    return 0;
}
