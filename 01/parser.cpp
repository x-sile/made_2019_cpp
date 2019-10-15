#include <iostream>

// number starting with zero is considered to be valid
// string starting with '+' is considered to be invalid as unary '+' is not required

class Parser {
    int index;
    std::string parse_string;

private:
    char get_next_char();
    int parse_add();
    int parse_mul();
    int parse_number();

public:
    int parse(const std::string &);
};

char Parser::get_next_char() {
    char next_char = parse_string[index];
    index++;
    return next_char;
}

int Parser::parse_add() {
    int op1 = parse_mul();
    while ((parse_string[index] == '+') || (parse_string[index] == '-')) {
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
    while ((parse_string[index] == '*') || (parse_string[index] == '/')) {
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
    while ((cur_char == '-') || (cur_char == ' ')) {
        if (cur_char == '-') {
            if (cur_string == "-") {
                cur_string = "";
            } else {
                cur_string = "-";
            }
        }
        cur_char = get_next_char();
    }
    if (!isdigit(cur_char)) {
        throw std::invalid_argument("Invalid symbol sequence at position " + std::to_string(index - 1));
    }
    cur_string += cur_char;
    while (isdigit(parse_string[index]) || (parse_string[index] == ' ')) {
        if (parse_string[index] == ' ') {
            index++;
        } else {
            cur_string += get_next_char();
        }
    }
    try {
        return std::stoi(cur_string);
    } catch (std::out_of_range  &error_msg) {
        throw std::invalid_argument("Value " + cur_string + " is too large for int");
    }
}

int Parser::parse(const std::string &input_string) {
    index = 0;
    parse_string = input_string;

    int result = parse_add();
    if (index != parse_string.length()) {
        throw std::invalid_argument("Invalid symbol sequence at position " + std::to_string(index));
    }
    return result;

}
