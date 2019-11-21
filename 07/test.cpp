#include "string_format.h"
#include <iostream>
#include <cassert>

int main() {
    assert(format("{1}+{1} = {0}", 2, "one") == "one+one = 2");

    assert(format("{1}+{1} = {0}", 4, 2, "test", "asd", true) == "2+2 = 4");

    assert(format("555", 4, 2, "test", "asd", true) == "555");

    int a = 2;
    std::string b = "one";
    assert(format("{1}+{1} = {0}", a, b) == "one+one = 2");

    assert(format("{1}  +-d-2dsad ? {0}{0}{1} {2}", a, true, 234) == "1  +-d-2dsad ? 221 234");

    std::cout << "Tests passed!" << std::endl;
    return EXIT_SUCCESS;
}
