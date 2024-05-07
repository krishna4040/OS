def fcfs_scheduling(processes):
    # Sort processes based on arrival time (if not already sorted)
    processes.sort(key=lambda x: x[1])
    
    # Initialize variables
    total_processes = len(processes)
    current_time = 0
    total_waiting_time = 0
    
    # Iterate through each process
    for process in processes:
        process_id, arrival_time, burst_time = process
        
        # If arrival time is after the current time, update current time
        if arrival_time > current_time:
            current_time = arrival_time
        
        # Calculate waiting time for the current process
        waiting_time = max(0, current_time - arrival_time)
        total_waiting_time += waiting_time
        
        # Update current time to account for execution time of current process
        current_time += burst_time
        
        # Print process information
        print(f"Process {process_id}: Arrival Time={arrival_time}, Burst Time={burst_time}, Waiting Time={waiting_time}")
    
    # Calculate average waiting time
    average_waiting_time = total_waiting_time / total_processes
    print(f"Average Waiting Time: {average_waiting_time}")

# Example usage:
processes = [
    (1, 0, 3),
    (2, 2, 6),
    (3, 4, 4),
    (4, 6, 5)
]

fcfs_scheduling(processes)
