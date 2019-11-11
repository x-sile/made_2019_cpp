#pragma once

#include <iostream>


enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream &out_) : out(out_) {}

    template<class... Args>
    Error operator()(Args &&... args) {
        return process(std::forward<Args>(args)...);
    }

    template<class T>
    Error save(T &object) {
        return object.serialize(*this);
    }

private:
    std::ostream &out;

    template<class T, class... Args>
    Error process(T &&first, Args &&... rest) {
        Error err1 = process(std::forward<T>(first));
        Error err2 = process(std::forward<Args>(rest)...);
        if ((err1 != Error::CorruptedArchive) && (err2 != Error::CorruptedArchive)) return Error::NoError;
        return Error::CorruptedArchive;
    }

    Error process(uint64_t value) {
        out << value << Separator;
        return Error::NoError;
    }

    Error process(bool value) {
        out << (value ? "true" : "false") << Separator;
        return Error::NoError;
    }

    template<class T>
    Error process(T &&other) {
        return Error::CorruptedArchive;
    }
};
