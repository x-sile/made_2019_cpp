#pragma once

#include <iterator>

template<class T>
class Iterator :
        public std::iterator<std::random_access_iterator_tag, T> {
    T *ptr_;
public:
    explicit Iterator(T *ptr) : ptr_(ptr) {}

    bool operator==(const Iterator<T> &other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T> &other) const {
        return !(*this == other);
    }

    bool operator<(const Iterator<T> &other) const {
        return ptr_ < other.ptr_;
    }

    bool operator<=(const Iterator<T> &other) const {
        return !(other < this);
    }

    bool operator>(const Iterator<T> &other) const {
        return other < this;
    }

    bool operator>=(const Iterator<T> &other) const {
        return !(this < other);
    }

    typename Iterator::reference operator*() const {
        return *ptr_;
    }

    Iterator &operator++() {
        ++ptr_;
        return *this;
    }

    Iterator operator++(int) {
        Iterator tmp(*this);
        ++ptr_;
        return tmp;
    }

    Iterator &operator--() {
        --ptr_;
        return *this;
    }

    Iterator operator--(int) {
        Iterator tmp(*this);
        --ptr_;
        return tmp;
    }

    Iterator operator+(int add) const {
        Iterator tmp(*this);
        tmp.ptr_ += add;
        return tmp;
    }

    Iterator operator-(int sub) const {
        Iterator tmp(*this);
        tmp.ptr_ -= sub;
        return tmp;
    }

    Iterator &operator+=(int add) {
        ptr_ += add;
        return *this;
    }

    Iterator &operator-=(int sub) {
        ptr_ -= sub;
        return *this;
    }
};
