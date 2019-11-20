#include "bigint.h"
#include <iostream>
#include <cassert>
#include <sstream>

int main() {
    BigInt x1 = -523434;
    BigInt x2 = 1235;
    BigInt x3 = "-5342";
    BigInt x4 = "9934343";

    std::stringstream s;

    s << x1;
    assert(s.str() == "-523434");
    s.str("");

    BigInt x5;
    x5 = x1;
    s << x5;
    assert(s.str() == "-523434");
    s.str("");

    BigInt x6 = x1;
    s << x6;
    assert(s.str() == "-523434");
    s.str("");

    BigInt x7;
    x7 = std::move(x5);
    s << x7;
    assert(s.str() == "-523434");
    s.str("");

    BigInt x8 = std::move(x6);
    s << x8;
    assert(s.str() == "-523434");
    s.str("");

    s << x3;
    assert(s.str() == "-5342");
    s.str("");

    assert(x1 < x2);
    assert(x2 > x1);
    assert(x1 == -523434);
    assert(x1 != 523434);
    assert(x1 >= -523434);
    assert(x1 <= -523434);
    assert(x1 == x1);
    assert(-x1 == 523434);

    assert(x1 + x2 == -522199);
    assert(x2 + x1 == -522199);
    assert(x1 + x3 == -528776);
    assert(x1 + x4 == 9410909);
    assert(x2 + x3 == -4107);
    assert(x2 + x4 == 9935578);
    assert(x3 + x4 == 9929001);
    assert(x3 + 999999999 == 999994657);
    assert(x3 + "999999999" == 999994657);
    assert(x3 + "999999999999999999999999999999999999" == "999999999999999999999999999999994657");

    assert(x1 - x2 == -524669);
    assert(x2 - x1 == 524669);
    assert(x1 - x3 == -518092);
    assert(x1 - x4 == -10457777);
    assert(x2 - x3 == 6577);
    assert(x2 - x4 == -9933108);
    assert(x3 - x4 == -9939685);
    assert(x3 - 10000000 == -10005342);
    assert(x3 - "10000000000000000000000000000000000" == "-10000000000000000000000000000005342");

    std::cout << "Tests passed!" << std::endl;
    return EXIT_SUCCESS;
}
