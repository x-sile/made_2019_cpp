#include <iostream>
#include <cstring>
#include "bigint.h"

BigInt::BigInt(const char *str) {
    initialize(str);
}

BigInt::BigInt(int value) {
    initialize(std::to_string(value).c_str());
}

BigInt::BigInt(const BigInt &copied)
        : data_(new char[copied.size_])
        , size_(copied.size_)
        , isNegative_(copied.isNegative_) {
    std::copy(copied.data_, copied.data_ + size_, data_);
}

BigInt &BigInt::operator=(const BigInt &copied) {
    if (this == &copied)
        return *this;
    char *tmp = new char[copied.size_];
    delete[] data_;
    data_ = tmp;
    size_ = copied.size_;
    isNegative_ = copied.isNegative_;
    std::copy(copied.data_, copied.data_ + size_, data_);
    return *this;
}

BigInt::BigInt(BigInt &&moved)
        : data_(moved.data_)
        , size_(moved.size_)
        , isNegative_(moved.isNegative_) {
    moved.data_ = nullptr;
    moved.size_ = 0;
}

BigInt &BigInt::operator=(BigInt &&moved) {
    if (this == &moved)
        return *this;
    delete[] data_;
    data_ = moved.data_;
    size_ = moved.size_;
    isNegative_ = moved.isNegative_;
    moved.data_ = nullptr;
    moved.size_ = 0;
    return *this;
}

BigInt::~BigInt() {
    delete[] data_;
}

BigInt BigInt::operator+(const BigInt &other) const {
    BigInt tmp(*this);
    size_t tmp_size = std::max(size_, other.size_);
    char *tmp_data_ = new char[tmp_size];
    int i = size_ - 1;
    int j = other.size_ - 1;
    int k = tmp_size - 1;
    int res = 0;
    if (isNegative_ == other.isNegative_) {
        tmp.isNegative_ = isNegative_;
        int resid = 0;
        while ((i >= 0) || (j >= 0)) {
            int num1 = i >= 0 ? data_[i] - '0' : 0;
            int num2 = j >= 0 ? other.data_[j] - '0' : 0;
            res = num1 + num2 + resid;
            resid = res / 10;
            res %= 10;
            tmp_data_[k] = res + '0';
            i--;
            j--;
            k--;
        }
        if (resid > 0) {
            char *tmp_data_2 = new char[tmp_size + 1];
            tmp_data_2[0] = resid + '0';
            std::copy(tmp_data_, tmp_data_ + tmp_size, tmp_data_2 + 1);
            delete[] tmp_data_;
            tmp.data_ = tmp_data_2;
            tmp.size_ = tmp_size + 1;
        } else {
            tmp.data_ = tmp_data_;
            tmp.size_ = tmp_size;
        }
    } else {
        if ((!isNegative_ && (*this >= (-other))) || (isNegative_ && (*this <= (-other)))) {
            tmp.isNegative_ = isNegative_;
            int extra = 0;
            while ((i >= 0) || (j >= 0)) {
                int num1 = i >= 0 ? data_[i] - '0' : 0;
                int num2 = j >= 0 ? other.data_[j] - '0' : 0;
                res = num1 - extra - num2;
                if (res < 0) {
                    res += 10;
                    extra = 1;
                } else {
                    extra = 0;
                }
                tmp_data_[k] = res + '0';
                i--;
                j--;
                k--;
            }
        } else {
            tmp.isNegative_ = other.isNegative_;
            int extra = 0;
            while ((i >= 0) || (j >= 0)) {
                int num1 = i >= 0 ? data_[i] - '0' : 0;
                int num2 = j >= 0 ? other.data_[j] - '0' : 0;
                res = num2 - extra - num1;
                if (res < 0) {
                    res += 10;
                    extra = 1;
                } else {
                    extra = 0;
                }
                tmp_data_[k] = res + '0';
                i--;
                j--;
                k--;
            }
        }
        size_t start_ptr = 0;
        while ((tmp_data_[start_ptr] == '0') && (start_ptr < tmp_size)) {
            start_ptr++;
        }
        if (start_ptr > 0) {
            tmp_size -= start_ptr;
            char *tmp_data_2 = new char[tmp_size];
            std::copy(tmp_data_ + start_ptr, tmp_data_ + start_ptr + tmp_size, tmp_data_2);
            delete[] tmp_data_;
            tmp.data_ = tmp_data_2;
        } else {
            tmp.data_ = tmp_data_;
        }
        tmp.size_ = tmp_size;
    }
    return tmp;
}

BigInt BigInt::operator-(const BigInt &other) const {
    return *this + (-other);
}

BigInt BigInt::operator-() const {
    BigInt tmp(*this);
    tmp.isNegative_ = !isNegative_;
    return tmp;
}

bool BigInt::operator==(const BigInt &other) const {
    if (this == &other)
        return true;

    if ((size_ != other.size_) || (isNegative_ != other.isNegative_)) {
        return false;
    }

    for (size_t i = 0; i < size_; i++)
        if (data_[i] != other.data_[i])
            return false;

    return true;
}

bool BigInt::operator!=(const BigInt &other) const {
    return !(*this == other);
}

bool BigInt::operator>(const BigInt &other) const {
    if (this == &other)
        return false;

    if ((!isNegative_) && (other.isNegative_)) {
        return true;
    } else if ((isNegative_) && (!other.isNegative_)) {
        return false;
    } else if ((isNegative_ && other.isNegative_)) {
        if (size_ < other.size_) {
            return true;
        } else if (size_ > other.size_) {
            return false;
        } else {
            for (size_t i = 0; i < size_; i++)
                if (data_[i] < other.data_[i])
                    return true;
                else if (data_[i] > other.data_[i]) {
                    return false;
                }
        }
    } else {
        if (size_ < other.size_) {
            return false;
        } else if (size_ > other.size_) {
            return true;
        } else {
            for (size_t i = 0; i < size_; i++)
                if (data_[i] < other.data_[i])
                    return false;
                else if (data_[i] > other.data_[i]) {
                    return true;
                }
        }
    }
    return false;
}

bool BigInt::operator>=(const BigInt &other) const {
    return !(other > *this);
}

bool BigInt::operator<(const BigInt &other) const {
    return other > *this;
}

bool BigInt::operator<=(const BigInt &other) const {
    return !(*this > other);
}

std::ostream &operator<<(std::ostream &out, const BigInt &bigint) {
    if (bigint.isNegative_) {
        out << '-';
    }
    for (size_t i = 0; i < bigint.size_; i++) {
        out << bigint.data_[i];
    }
    return out;
}

void BigInt::initialize(const char *str) {
    isNegative_ = str[0] == '-';
    int skipFirst = isNegative_;
    size_ = std::strlen(str) - skipFirst;
    data_ = new char[size_ - skipFirst];
    std::copy(str + skipFirst, str + skipFirst + size_, data_);
}

BigInt operator+(const int &x, const BigInt &y) {
    return BigInt(x) + y;
}

BigInt operator-(const int &x, const BigInt &y) {
    return BigInt(x) - y;
}

bool operator==(const int &x, const BigInt &y) {
    return BigInt(x) == y;
}

bool operator!=(const int &x, const BigInt &y) {
    return BigInt(x) != y;
}

bool operator>(const int &x, const BigInt &y) {
    return BigInt(x) > y;
}

bool operator>=(const int &x, const BigInt &y) {
    return BigInt(x) >= y;
}

bool operator<(const int &x, const BigInt &y) {
    return BigInt(x) < y;
}

bool operator<=(const int &x, const BigInt &y) {
    return BigInt(x) <= y;
}
