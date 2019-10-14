#include <iostream>
#include <string>
#include <regex>

// number starting with zero is considered to be valid
// string starting with '+' is considered to be invalid as unary '+' is not required

class Parser {
    int index;
    std::string parse_string;

private:
    char look_next_char();
    char get_next_char();
    int parse_add();
    int parse_mul();
    int parse_number();

public:
    int parse(std::string &);
};

char Parser::look_next_char() {
    return parse_string[index];
}

char Parser::get_next_char() {
    char next_char = look_next_char();
    index++;
    return next_char;
}

int Parser::parse_add() {
    int op1 = parse_mul();
    while ((look_next_char() == '+') || (look_next_char() == '-')) {
        char operation = get_next_char();
        int op2 = parse_mul();
        if (operation == '+') {
            op1 = op1 + op2;
        } else {
            op1 = op1 - op2;
        }
    }
    return op1;
}

int Parser::parse_mul() {
    int op1 = parse_number();
    while ((look_next_char() == '*') || (look_next_char() == '/')) {
        char operation = get_next_char();
        int op2 = parse_number();
        if (operation == '*') {
            op1 = op1 * op2;
        } else {
            if (op2 == 0) {
                throw std::invalid_argument("Division by zero");
            }
            op1 = op1 / op2;
        }
    }
    return op1;

}

int Parser::parse_number() {
    std::string cur_string;

    char cur_char = get_next_char();
    while (cur_char == '-') {
        cur_string += "-";
        cur_char = get_next_char();
    }
    if (cur_string.length() % 2 == 1) {
        cur_string = "-";
    } else {
        cur_string = "";
    }
    if (!isdigit(cur_char)) {
        throw std::invalid_argument("Invalid symbol sequence at position " + std::to_string(index - 1));
    }
    cur_string += cur_char;
    while (isdigit(look_next_char())) {
        cur_string += get_next_char();
    }
    return std::stoi(cur_string);
}

int Parser::parse(std::string &input_string) {
    index = 0;
    parse_string = std::regex_replace(input_string, std::regex("\\s+"), "");
    int result = parse_add();
    if (index != parse_string.length()) {
        throw std::invalid_argument("Invalid symbol sequence at position " + std::to_string(index));
    }
    return result;

}
