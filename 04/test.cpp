#include "matrix.h"
#include <iostream>
#include <cassert>

int main() {
    Matrix m1(5, 10);
    assert(m1.getRows() == 5);
    assert(m1.getColumns() == 10);

    Matrix m2(5, 10);
    m1[1][4] = 2;
    m1[3][1] = 15;
    m2[1][4] = 2;
    m2[3][1] = 15;
    assert(m1 == m2);

    m2[4][4] = 2;
    assert(m1 != m2);

    int mult = 3;
    m1 *= mult;
    Matrix m3(5, 10);
    m3[1][4] = 2 * mult;
    m3[3][1] = 15 * mult;
    assert(m1 == m3);
    assert(m1[1][4] == 6);
    assert(m1[3][1] == 45);

    const Matrix m4(2, 3);
    const Matrix m5(2, 3);
    assert(m4 == m5);
    assert(m4[0][0] == 0);

    try {
        m1[1][10];
    } catch (std::out_of_range &err_msg) {
        std::cout << "Tests passed!" << std::endl;
        return EXIT_SUCCESS;
    }

    std::cout << "Tests failed!" << std::endl;
    return EXIT_FAILURE;
}
