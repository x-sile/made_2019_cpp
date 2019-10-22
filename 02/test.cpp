#include "allocator.h"
#include <cassert>

int main() {
    LinearAllocator allocator{sizeof(int) * 100};

    int *arr1 = (int *) allocator.alloc(sizeof(int) * 5);
    assert(arr1 != nullptr);
    int *arr2 = (int *) allocator.alloc(sizeof(int) * 50);
    assert(arr2 != nullptr);
    assert(arr2 == arr1 + 5);
    int *arr3 = (int *) allocator.alloc(sizeof(int) * 45);
    assert(arr3 != nullptr);
    assert(arr3 == arr2 + 50);
    int *arr4 = (int *) allocator.alloc(sizeof(int) * 1);
    assert(arr4 == nullptr);
    allocator.reset();
    int *arr5 = (int *) allocator.alloc(sizeof(int) * 10);
    assert(arr5 != nullptr);
    int *arr6 = (int *) allocator.alloc(sizeof(int) * 90);
    assert(arr6 == arr5 + 10);
    allocator.reset();
    arr5[0] = 1;
    arr5[9] = 1;
    arr5[10] = 10;
    assert(arr5[10] == 10);
    arr6[0] = 11;
    assert(arr5[10] == 11);
    assert(arr1 == arr5);

    try {
        LinearAllocator bigAllocator{sizeof(int) * 1024 * 1024 * 1024 * 1024};
    } catch (const std::invalid_argument &error_msg) {
        std::cout << "Tests passed!" << std::endl;
        return EXIT_SUCCESS;
    }
    std::cout << "Tests failed!" << std::endl;
    return EXIT_FAILURE;
}
