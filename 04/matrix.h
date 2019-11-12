#include <iostream>

class Matrix {
private:
    const size_t nrows;
    const size_t ncols;
    int *arr;
public:
    Matrix(size_t nrows_, size_t ncols_) : nrows(nrows_), ncols(ncols_) { arr = new int[nrows_ * ncols_]; };
    int getRows() const { return nrows; };
    int getColumns() const { return ncols; };

    // прокси-класс
    class Array {
    private:
        const Matrix &matrix;
        const size_t row;
    public:
        Array(const Matrix &matrix_, size_t row_) : matrix(matrix_), row(row_) {};
        // для const и non-const матриц
        int &operator[](size_t col);
        const int &operator[](size_t col) const;
    };
    //
    
    Array operator[](size_t row) { return Array{*this, row}; };
    const Array operator[](size_t row) const { return Array{*this, row}; };
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
    Matrix &operator*=(int mult);
    ~Matrix() { delete[] arr; };;
};
