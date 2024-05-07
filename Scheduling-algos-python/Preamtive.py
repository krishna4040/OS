import heapq

class Process:
    def __init__(self, pid, arrival_time, burst_time, priority):
        self.pid = pid
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.priority = priority
    
    def __lt__(self, other):
        # Define comparison based on priority (lower priority value means higher priority)
        return self.priority < other.priority

def preemptive_priority_scheduling(processes):
    # Priority queue to store processes based on their arrival time
    ready_queue = []
    # Current time
    current_time = 0
    # List to store waiting times for each process
    waiting_times = {}
    
    # Index to track the next process to arrive
    next_process_index = 0
    
    # Loop until there are no more processes in the queue or arriving
    while ready_queue or next_process_index < len(processes):
        # Check if there are any processes arriving at this time
        while next_process_index < len(processes) and processes[next_process_index].arrival_time == current_time:
            # Push the process to the ready queue
            heapq.heappush(ready_queue, processes[next_process_index])
            # Move to the next process
            next_process_index += 1
        
        # If the ready queue is not empty, execute the process with the highest priority
        if ready_queue:
            # Pop the process with the highest priority
            current_process = heapq.heappop(ready_queue)
            # Update waiting time for the current process
            waiting_times[current_process.pid] = current_time - current_process.arrival_time
            # Increment current time by burst time of the current process
            current_time += current_process.burst_time
            # Print process execution information
            print(f"Process {current_process.pid} executed. Priority: {current_process.priority}, Waiting Time: {waiting_times[current_process.pid]}")
            # Reduce burst time of the current process by 1
            current_process.burst_time -= 1
            # If burst time is remaining, push the process back to the ready queue
            if current_process.burst_time > 0:
                heapq.heappush(ready_queue, current_process)
        else:
            # If there are no processes in the ready queue, move to the next arrival time
            current_time = processes[next_process_index].arrival_time
    
    # Calculate and print average waiting time
    total_waiting_time = sum(waiting_times.values())
    average_waiting_time = total_waiting_time / len(processes)
    print(f"Average Waiting Time: {average_waiting_time}")

# Example usage:
processes = [
    Process(1, 0, 6, 3),
    Process(2, 2, 8, 1),
    Process(3, 4, 7, 2)
]

preemptive_priority_scheduling(processes)
