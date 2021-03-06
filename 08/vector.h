#pragma once

#include "iterator.h"

template<class T, class Alloc = std::allocator<T>>
class vector {
public:
    using size_type = size_t;
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    using const_reference = const T &;
    using allocator_type = Alloc;
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;

    vector() : data_(allocator_.allocate(INIT_CAPACITY_)), size_(0), capacity_(INIT_CAPACITY_) {
        for (size_t i = 0; i < capacity_; i++) {
            allocator_.construct(&data_[i], T());
        }
    }

    explicit vector(size_type count) : data_(allocator_.allocate(count)), size_(0), capacity_(count) {
        for (size_t i = 0; i < capacity_; i++) {
            allocator_.construct(&data_[i], T());
        }
    }

    vector(size_type count, const value_type &defaultValue)
            : data_(allocator_.allocate(count)), size_(count), capacity_(count) {
        for (size_t i = 0; i < capacity_; i++) {
            allocator_.construct(&data_[i], defaultValue);
        }
    }

    vector(std::initializer_list<value_type> init) {
        size_t i = 0;
        auto current = init.begin();
        const auto end = init.end();
        size_type count = end - current;
        data_ = allocator_.allocate(count);
        size_ = capacity_ = count;
        while (current != end) {
            allocator_.construct(&data_[i++], *current++);
        }
    }

    vector(const vector &copied)
            : data_(allocator_.allocate(copied.capacity_)), size_(copied.size_), capacity_(copied.capacity_) {
        for (size_t i = 0; i < size_; i++) {
            allocator_.construct(&data_[i], copied.data_[i]);
        }
    }

    vector &operator=(const vector &copied) {
        if (this == &copied)
            return *this;
        pointer tmp = allocator_.allocate(copied.capacity_);
        clear();
        allocator_.deallocate(data_, capacity_);
        data_ = tmp;
        size_ = copied.size_;
        capacity_ = copied.capacity_;
        for (size_t i = 0; i < size_; i++) {
            allocator_.construct(&data_[i], copied.data_[i]);
        }
        return *this;
    }

    vector(vector &&moved)
            : data_(moved.data_), size_(moved.size_), capacity_(moved.capacity_) {
        moved.data_ = nullptr;
        moved.size_ = 0;
        moved.capacity_ = 0;
    }

    vector &operator=(vector &&moved) {
        if (this == &moved)
            return *this;
        clear();
        allocator_.deallocate(data_, capacity_);
        data_ = moved.data_;
        size_ = moved.size_;
        capacity_ = moved.capacity_;
        moved.data_ = nullptr;
        moved.size_ = 0;
        moved.capacity_ = 0;
        return *this;
    }

    iterator begin() noexcept {
        return iterator(data_);
    }

    iterator end() noexcept {
        return iterator(data_ + size_);
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    reference operator[](size_type pos) {
        return data_[pos];
    }

    const_reference operator[](size_type pos) const {
        return data_[pos];
    }

    void push_back(value_type &&value) {
        if (size_ == capacity_) {
            reallocate_(capacity_ * SIZE_MULT_);
        }
        data_[size_++] = std::move(value);
    }

    void push_back(const value_type &value) {
        if (size_ == capacity_) {
            reallocate_(capacity_ * SIZE_MULT_);
        }
        data_[size_++] = value;
    }

    void pop_back() {
        allocator_.destroy(&data_[--size_]);
    }

    void reserve(size_type count) {
        if (count > capacity_) {
            reallocate_(count);
        }
    }

    size_type capacity() const noexcept {
        return capacity_;
    }

    void resize(size_type newSize) {
        if (newSize != size_) {
            reallocate_(newSize);
        }
    }

    void resize(size_type newSize, const value_type &defaultValue) {
        if (newSize != size_) {
            reallocate_(newSize, defaultValue);
        }
    }

    size_type size() const noexcept {
        return size_;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    void clear() noexcept {
        for (size_type i = 0; i < size_; i++) {
            allocator_.destroy(&data_[i]);
        }
        size_ = 0;
    }

    ~vector() {
        clear();
        allocator_.deallocate(data_, capacity_);
        data_ = nullptr;
    }

private:
    T *data_;
    size_type size_;
    size_type capacity_;
    allocator_type allocator_;
    static constexpr int SIZE_MULT_ = 2;
    static constexpr int INIT_CAPACITY_ = 8;

    void reallocate_(size_type count, const value_type &defaultValue = T()) {
        pointer tmp = allocator_.allocate(count);
        size_type newSize = std::min(size_, count);
        for (size_t i = 0; i < count; i++) {
            if (i < newSize) {
                allocator_.construct(&tmp[i], data_[i]);
            } else {
                allocator_.construct(&tmp[i], defaultValue);
            }
        }
        clear();
        allocator_.deallocate(data_, capacity_);
        data_ = tmp;
        size_ = newSize;
        capacity_ = count;
    }
};
