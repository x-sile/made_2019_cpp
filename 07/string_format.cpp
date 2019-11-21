#include <iostream>
#include <vector>

std::string process(const std::string &str, const std::vector<std::string> &arr) {
    std::string formatted;
    std::string arg;
    int arg_number;
    size_t i = 0;
    while (i < str.size()) {
        if (str[i] == '{') {
            i++;
            while (isdigit(str[i])) {
                arg += str[i++];
            }
            if ((str[i] != '}') || arg.empty()) {
                throw std::runtime_error("Wrong string");
            }
            try {
                arg_number = std::stoi(arg);
            } catch (std::out_of_range &error_msg) {
                throw std::runtime_error("Wrong string");
            }
            if (arg_number >= arr.size()) {
                throw std::runtime_error("Wrong string");
            }
            formatted += arr[arg_number];
            arg = "";
        } else if (str[i] == '}') {
            throw std::runtime_error("Wrong string");
        } else {
            formatted += str[i];
        }
        i++;
    }
    return formatted;
}