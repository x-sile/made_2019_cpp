#include <iostream>

class LinearAllocator {
private:
    size_t memory_left;
    size_t offset;
    char *head_block_ptr;

public:
    LinearAllocator(size_t maxSize);
    char *alloc(size_t size);
    void reset();
    ~LinearAllocator();
};

LinearAllocator::LinearAllocator(size_t maxSize) {
    memory_left = maxSize;
    offset = 0;
    head_block_ptr = (char *) malloc(maxSize);
    if (head_block_ptr == nullptr) {
        throw std::invalid_argument("Not enough memory");
    }
}

char *LinearAllocator::alloc(size_t size) {
    if (size > memory_left) {
        return nullptr;
    }
    memory_left -= size;
    offset += size;
    return head_block_ptr + offset - size;
}

void LinearAllocator::reset() {
    memory_left += offset;
    offset = 0;
}

// unnecessary hear bud good practice to free memory for each malloc
LinearAllocator::~LinearAllocator() {
    free(head_block_ptr);
}
