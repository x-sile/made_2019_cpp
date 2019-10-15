#include <iostream>

class Parser {
    int index;
    std::string parse_string;

private:
    char get_next_char();
    int parse_add();
    int parse_mul();
    int parse_number();

public:
    int parse(const std::string&);
};
