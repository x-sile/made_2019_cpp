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
        construct_(0, capacity_);
    }

    explicit vector(size_type count) : data_(allocator_.allocate(count)), size_(0), capacity_(count) {
        construct_(0, capacity_);
    }

    vector(size_type count, const value_type &defaultValue)
            : data_(allocator_.allocate(count)), size_(count), capacity_(count) {
        construct_(0, capacity_);
        std::fill(data_, data_ + size_, defaultValue);
    }

    vector(std::initializer_list<value_type> init) {
        size_t i = 0;
        auto current = init.begin();
        const auto end = init.end();
        size_type count = end - current;
        data_ = allocator_.allocate(count);
        size_ = capacity_ = count;
        construct_(0, capacity_);
        while (current != end) {
            data_[i++] = *current++;
        }
    }

    vector(const vector &copied)
            : data_(allocator_.allocate(copied.capacity_)), size_(copied.size_), capacity_(copied.capacity_) {
        std::copy(copied.data_, copied.data_ + size_, data_);
    }

    vector &operator=(const vector &copied) {
        if (this == &copied)
            return *this;
        pointer tmp = allocator_.allocate(copied.capacity_);
        allocator_.deallocate(data_, capacity_);
        data_ = tmp;
        size_ = copied.size_;
        capacity_ = copied.capacity_;
        construct_(0, capacity_);
        std::copy(copied.data_, copied.data_ + size_, data_);
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
        size_--;
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
            reallocate_(newSize);
            if (newSize > size_) {
                std::fill(data_ + size_, data_ + newSize, defaultValue);
            }
        }
    }

    size_type size() const noexcept {
        return size_;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    void clear() noexcept {
        size_ = 0;
    }

    ~vector() {
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

    void reallocate_(size_type count) {
        pointer tmp = allocator_.allocate(count);
        for (size_t i = 0; i < count; i++) {
            allocator_.construct(&tmp[i], T());
        }
        size_type newSize = std::min(size_, count);
        std::copy(data_, data_ + newSize, tmp);
        allocator_.deallocate(data_, capacity_);
        data_ = tmp;
        size_ = newSize;
        capacity_ = count;
    }

    void construct_(size_type from_, size_type to_) {
        for (size_t i = from_; i < to_; i++) {
            allocator_.construct(&data_[i], T());
        }
    }
};
