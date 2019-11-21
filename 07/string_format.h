#pragma once

#include <iostream>
#include <vector>
#include <sstream>

template<class T>
void get_args(std::vector<std::string> &arr, T &&arg) {
    std::stringstream stream;
    stream << arg;
    arr.emplace_back(stream.str());
}

template<class T, class... Args>
void get_args(std::vector<std::string> &arr, T &&first, Args &&... rest) {
    get_args(arr, std::forward<T>(first));
    get_args(arr, std::forward<Args>(rest)...);
}

std::string process(const std::string &str, const std::vector<std::string> &arr);

template<class... Args>
std::string format(const std::string &str, Args &&... args) {
    std::vector<std::string> arr;
    get_args(arr, std::forward<Args>(args)...);
    return process(str, arr);
}
