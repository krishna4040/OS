from collections import deque

def fifo_page_replacement(pages, capacity):
    page_queue = deque()  # Queue to hold pages in memory
    page_set = set()      # Set to track pages currently in memory
    page_faults = 0       # Counter for page faults

    for page in pages:
        # If page not in memory, handle page fault
        if page not in page_set:
            # If memory is full, evict the oldest page (front of queue)
            if len(page_queue) == capacity:
                oldest_page = page_queue.popleft()
                page_set.remove(oldest_page)

            # Add the new page to memory
            page_queue.append(page)
            page_set.add(page)
            page_faults += 1

    return page_faults

# Example pages and memory capacity
pages = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2]
capacity = 4

# Execute FIFO page replacement algorithm
page_faults = fifo_page_replacement(pages, capacity)

print("Total page faults using FIFO:", page_faults)
