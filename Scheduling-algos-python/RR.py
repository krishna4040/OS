from collections import deque

def round_robin(processes, time_quantum):
    # Create a queue to store processes
    process_queue = deque(processes)
    
    # Initialize variables
    current_time = 0
    total_waiting_time = 0
    
    # Process the queue until it's empty
    while process_queue:
        process_id, burst_time = process_queue.popleft()
        
        # Determine the time to execute this process
        execute_time = min(burst_time, time_quantum)
        
        # Update waiting time for all processes in the queue
        for _, bt in process_queue:
            total_waiting_time += min(bt, time_quantum)
        
        # Update burst time of the current process
        burst_time -= execute_time
        
        # Update current time
        current_time += execute_time
        
        # If process still has burst time, reinsert it into the queue
        if burst_time > 0:
            process_queue.append((process_id, burst_time))
        
        # Print process information
        print(f"Process {process_id} executed for {execute_time} units. Remaining burst time: {burst_time}")
    
    # Calculate average waiting time
    average_waiting_time = total_waiting_time / len(processes)
    print(f"Average Waiting Time: {average_waiting_time}")

# Example usage:
processes = [
    (1, 10),
    (2, 5),
    (3, 8),
    (4, 4)
]
time_quantum = 4

round_robin(processes, time_quantum)
