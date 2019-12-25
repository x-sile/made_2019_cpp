#include "threadpull.h"

#include <algorithm>
#include <iostream>
#include <cassert>


int main() {
    ThreadPool pool(8);

    auto task1 = pool.exec([]() { return 1; });
    assert(task1.get() == 1);

    std::vector<int> unsorted{0, 5, 15, 3, 10, 7, 100, -123};
    std::vector<int> sorted{-123, 0, 3, 5, 7, 10, 15, 100};
    auto task2 = pool.exec([&unsorted]() { std::sort(unsorted.begin(), unsorted.end()); });
    task2.get();
    assert(unsorted == sorted);

    auto task3 = pool.exec([](int a = 3, int b = 5) { return a + b; });
    assert(task3.get() == 8);

    std::cout << "Tests passed!" << std::endl;
    return EXIT_SUCCESS;
}
