#include <iostream>
#include "matrix.h"

int& Matrix::Array::operator[](int col) const {
    if ((row >= matrix.nrows) || (row < 0)) {
        throw std::out_of_range("Row index is out of range");
    } else if ((col >= matrix.ncols) || (col < 0)) {
        throw std::out_of_range("Column index is out of range");
    }
    return matrix.arr[row * sizeof(int) + col];
}

Matrix::Array Matrix::operator[](int row) const {
    return Array{*this, row};
};

bool Matrix::operator==(const Matrix &other) const {
    if (this == &other) {
        return true;
    }
    for (int i = 0; i < nrows * ncols; i++) {
        if (arr[i] != other.arr[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &other) const {
    return !(*this == other);
}

Matrix& Matrix::operator*=(int mult) {
    for (int i = 0; i < nrows * ncols; i++) {
        arr[i] *= mult;
    }
    return *this;
}
