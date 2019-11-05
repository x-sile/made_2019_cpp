#include <iostream>

class Matrix {
private:
    const int nrows;
    const int ncols;
    int *arr;
public:
    Matrix(int nrows_, int ncols_) : nrows(nrows_), ncols(ncols_) { arr = new int[nrows_ * ncols_]; };
    int getRows() const { return nrows; };
    int getColumns() const { return ncols; };

    // прокси-класс
    class Array {
    private:
        const Matrix &matrix;
        const int row;
    public:
        Array(const Matrix &matrix_, int row_) : matrix(matrix_), row(row_) {};
        // возвращаю ссылку на int, чтобы можно было присваивать, не хак ли?
        int &operator[](int col) const;
    };
    //

    Array operator[](int row) const;
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
    Matrix &operator*=(int mult);
    ~Matrix() { delete[] arr; };;
};
