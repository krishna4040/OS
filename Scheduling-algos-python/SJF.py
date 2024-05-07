def sjf_scheduling(processes):
    # Sort processes based on burst time
    processes.sort(key=lambda x: x[1])
    
    # Initialize variables
    current_time = 0
    total_waiting_time = 0
    
    # Process the sorted list of processes
    for process_id, burst_time in processes:
        # Wait until current time reaches arrival time of the process
        if current_time < burst_time:
            current_time = burst_time
        
        # Calculate waiting time for the current process
        waiting_time = current_time - burst_time
        total_waiting_time += max(0, waiting_time)
        
        # Update current time to account for execution time of current process
        current_time += burst_time
        
        # Print process information
        print(f"Process {process_id}: Burst Time={burst_time}, Waiting Time={waiting_time}")
    
    # Calculate average waiting time
    average_waiting_time = total_waiting_time / len(processes)
    print(f"Average Waiting Time: {average_waiting_time}")

# Example usage:
processes = [
    (1, 6),
    (2, 8),
    (3, 7),
    (4, 3)
]

sjf_scheduling(processes)
