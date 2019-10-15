#include "parser.h"
#include <iostream>
#include "cassert"

using namespace std;

int main() {
    Parser parser;
    string expr;

    assert(parser.parse(expr.assign("2+2")) == 4);
    assert(parser.parse(expr.assign("---999-1")) == -1000);
    assert(parser.parse(expr.assign("-08+6*7/7-6")) == -8);
    assert(parser.parse(expr.assign("-08+6*7/7-6")) == -8);
    assert(parser.parse(expr.assign("10+---3*77/7--6*1")) == -17);
    assert(parser.parse(expr.assign("999/9/9/9+00000- -  - -0 0 0 0 0")) == 1);
    assert(parser.parse(expr.assign(" 0 0 0---12345")) == -12345);
    assert(parser.parse(expr.assign("-9")) == -9);
    assert(parser.parse(expr.assign("-0")) == 0);
    assert(parser.parse(expr.assign("  0   * 0 *0 +123--123+-123*2/2*2/3*3")) == 0);

    cout << "Tests passed!" << endl;
    return EXIT_SUCCESS;
}

