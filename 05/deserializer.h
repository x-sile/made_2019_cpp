#pragma once

#include "serializer.h"
#include <iostream>


class Deserializer {
public:
    explicit Deserializer(std::istream &in_) : in(in_) {}

    template<class... Args>
    Error operator()(Args &&... args) {
        return process(std::forward<Args>(args)...);
    }

    template<class T>
    Error load(T &object) {
        return object.serialize(*this);
    }

private:
    std::istream &in;

    template<class T, class... Args>
    Error process(T &&first, Args &&... rest) {
        Error err1 = process(std::forward<T>(first));
        Error err2 = process(std::forward<Args>(rest)...);
        if ((err1 != Error::CorruptedArchive) && (err2 != Error::CorruptedArchive)) return Error::NoError;
        return Error::CorruptedArchive;
    }

    Error process(uint64_t &value) {
        std::string text;
        in >> text;

        if (text.empty()) return Error::CorruptedArchive;

        for (auto ch: text) {
            if (!isdigit(ch)) {
                return Error::CorruptedArchive;
            }
        }
        value = std::strtoull(text.c_str(), nullptr, 10);
        return Error::NoError;
    }

    Error process(bool &value) {
        std::string text;
        in >> text;

        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }

    template<class T>
    Error process(T &&other) {
        return Error::CorruptedArchive;
    }
};
