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
