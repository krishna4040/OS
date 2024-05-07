#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

// Structure to represent a process
struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;  // Time when process starts execution
    int finish_time; // Time when process finishes execution

    // Constructor
    Process(int id, int arrival_time, int burst_time, int priority) : id(id), arrival_time(arrival_time), burst_time(burst_time), priority(priority), start_time(0), finish_time(0) {}

    // Comparison operator for priority queue
    bool operator<(const Process &other) const
    {
        return priority < other.priority; // Higher priority processes have lower values
    }
};

// Preemptive Priority Scheduling Algorithm
void preemptivePriorityScheduling(vector<Process> &processes)
{
    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.arrival_time < b.arrival_time; });

    int current_time = 0;
    priority_queue<Process> ready_queue;

    while (!processes.empty() || !ready_queue.empty())
    {
        // Check if any new processes have arrived
        while (!processes.empty() && processes.front().arrival_time <= current_time)
        {
            ready_queue.push(processes.front());
            processes.erase(processes.begin());
        }

        // Check if there are processes in the ready queue
        if (!ready_queue.empty())
        {
            Process current_process = ready_queue.top();
            ready_queue.pop();

            // Record start time if not already recorded
            if (current_process.start_time == 0)
                current_process.start_time = current_time;

            // Execute process for one time unit
            cout << "Process " << current_process.id << " is running..." << endl;
            current_process.burst_time--;

            // Check if process is completed
            if (current_process.burst_time > 0)
            {
                // Reinsert process into ready queue with updated priority
                ready_queue.push(current_process);
            }
            else
            {
                // Record finish time
                current_process.finish_time = current_time + 1;
                cout << "Process " << current_process.id << " completed!" << endl;
            }
        }
        else
        {
            // No processes ready, idle CPU
            cout << "CPU is idle..." << endl;
        }

        // Increment current time
        current_time++;
    }

    // Calculate turnaround time (TAT) and waiting time (WT) for each process
    for (auto &process : processes)
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
        Process(1, 0, 3, 3),
        Process(2, 2, 6, 1),
        Process(3, 4, 4, 2)};

    // Execute preemptive priority scheduling algorithm
    preemptivePriorityScheduling(processes);

    return 0;
}
