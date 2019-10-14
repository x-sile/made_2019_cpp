#include "parser.h"
#include <iostream>
#include <string>

int main() {
    Parser parser;
    std::string input_string;

    std::cout << "Enter valid arithmetic expression. Only +, -, *, / and unary minus are allowed!" << std::endl;
    std::getline(std::cin, input_string);
    try {
        int result = parser.parse(input_string);
        std::cout << result << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::invalid_argument &error_msg) {
        std::cout << error_msg.what() << std::endl;
        return EXIT_FAILURE;
    }
}
