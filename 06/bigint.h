#pragma once
#include <iostream>

class BigInt {
public:
    BigInt() : data_(nullptr), size_(0), isNegative_(false) {}
    BigInt(const char *str);
    BigInt(int value);
    BigInt(const BigInt &copied);
    BigInt &operator=(const BigInt &copied);
    BigInt(BigInt &&moved);
    BigInt &operator=(BigInt &&moved);
    ~BigInt();

    BigInt operator+(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;
    BigInt operator-() const;

    bool operator==(const BigInt &other) const;
    bool operator!=(const BigInt &other) const;
    bool operator>(const BigInt &other) const;
    bool operator>=(const BigInt &other) const;
    bool operator<(const BigInt &other) const;
    bool operator<=(const BigInt &other) const;

    friend BigInt operator+(const int &x, const BigInt &y);
    friend BigInt operator-(const int &x, const BigInt &y);
    friend bool operator==(const int &x, const BigInt &y);
    friend bool operator!=(const int &x, const BigInt &y);
    friend bool operator>(const int &x, const BigInt &y);
    friend bool operator>=(const int &x, const BigInt &y);
    friend bool operator<(const int &x, const BigInt &y);
    friend bool operator<=(const int &x, const BigInt &y);
    friend std::ostream &operator<<(std::ostream &out, const BigInt &bigint);

private:
    size_t size_;
    char *data_;
    bool isNegative_;

    void initialize(const char *str);
};
