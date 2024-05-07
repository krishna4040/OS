class MRUCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.cache = {}  # Dictionary to store key-value pairs

    def get(self, key):
        if key not in self.cache:
            return -1
        else:
            # Move the accessed key to the end to mark it as most recently used
            self.cache.move_to_end(key)
            return self.cache[key]

    def put(self, key, value):
        if key in self.cache:
            # Update the value and move the key to the end
            self.cache[key] = value
            self.cache.move_to_end(key)
        else:
            if len(self.cache) >= self.capacity:
                # Evict the most recently used key (last key in the dictionary)
                del self.cache[next(reversed(self.cache))]
            # Add the new key-value pair to the cache
            self.cache[key] = value

# Example usage:
cache = MRUCache(2)
cache.put(1, 1)
cache.put(2, 2)
print(cache.get(1))  # Output: 1 (1 is the most recently used)
cache.put(3, 3)       # evicts key 2
print(cache.get(2))  # Output: -1 (2 was evicted)
cache.put(4, 4)       # evicts key 1
print(cache.get(1))  # Output: -1 (1 was evicted)
print(cache.get(3))  # Output: 3 (3 is the most recently used)
print(cache.get(4))  # Output: 4 (4 is the most recently used)
