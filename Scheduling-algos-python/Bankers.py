class Banker:
    def __init__(self, allocation, max_need, available):
        self.allocation = allocation
        self.max_need = max_need
        self.available = available
        self.processes = len(allocation)
        self.resources = len(allocation[0])

    def is_safe_state(self, work, finish):
        need = [[self.max_need[i][j] - self.allocation[i][j] for j in range(self.resources)] for i in range(self.processes)]
        while True:
            found = False
            for i in range(self.processes):
                if not finish[i]:
                    if all(need[i][j] <= work[j] for j in range(self.resources)):
                        finish[i] = True
                        work = [work[j] + self.allocation[i][j] for j in range(self.resources)]
                        found = True
                        break
            if not found:
                break
        return all(finish)

    def request_resources(self, process_id, request):
        if all(request[i] <= self.available[i] for i in range(self.resources)):
            if all(request[i] <= self.max_need[process_id][i] - self.allocation[process_id][i] for i in range(self.resources)):
                new_allocation = [self.allocation[i][j] + (request[j] if i == process_id else 0) for i in range(self.processes) for j in range(self.resources)]
                if self.is_safe_state([self.available[i] - request[i] for i in range(self.resources)], [False] * self.processes):
                    self.allocation = [new_allocation[i * self.resources:(i + 1) * self.resources] for i in range(self.processes)]
                    self.available = [self.available[i] - request[i] for i in range(self.resources)]
                    return True, "Request granted."
                else:
                    return False, "Unsafe state. Request denied."
            else:
                return False, "Request exceeds maximum need. Request denied."
        else:
            return False, "Insufficient resources available. Request denied."

    def release_resources(self, process_id, release):
        if all(release[i] <= self.allocation[process_id][i] for i in range(self.resources)):
            self.allocation[process_id] = [self.allocation[process_id][i] - release[i] for i in range(self.resources)]
            self.available = [self.available[i] + release[i] for i in range(self.resources)]
            return True, "Resources released successfully."
        else:
            return False, "Release exceeds allocated resources."

# Example usage:
allocation = [[0, 1, 0], [2, 0, 0], [3, 0, 2], [2, 1, 1], [0, 0, 2]]
max_need = [[7, 5, 3], [3, 2, 2], [9, 0, 2], [2, 2, 2], [4, 3, 3]]
available = [3, 3, 2]

banker = Banker(allocation, max_need, available)

# Request resources for process 4
request_process_id = 4
request_resources = [1, 0, 2]
result, message = banker.request_resources(request_process_id, request_resources)
print(f"Request for process {request_process_id}: {message}")

# Release resources for process 1
release_process_id = 1
release_resources = [2, 0, 0]
result, message = banker.release_resources(release_process_id, release_resources)
print(f"Release for process {release_process_id}: {message}")
