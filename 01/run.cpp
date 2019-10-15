#include "parser.h"
#include <iostream>

int main(int argc, const char* argv[]) {
    Parser parser;

    if (argc < 2) {
        std::cout << "No arithmetic expression passed" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        int result = parser.parse(std::string(argv[1]));
        std::cout << result << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::invalid_argument &error_msg) {
        std::cout << error_msg.what() << std::endl;
        return EXIT_FAILURE;
    }
}
