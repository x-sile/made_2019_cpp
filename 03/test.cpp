#include "parser.h"
#include <iostream>
#include "cassert"

using namespace std;

int main() {
    Parser parser{};
    string str;
    vector<string> parsed_string;

    int token_count = 0;
    parser.addOnTokenCallback([&token_count](const string &token) { return token == "abc"; },
                              [&token_count](const string &token) { token_count++; });
    parser.parse(str.assign("asd kcj 823 abc   "));
    assert(token_count == 1);

    token_count = 0;
    parser.addOnTokenCallback([&token_count](const int &token) { return token == 823; },
                              [&token_count](const int &token) { token_count++; });
    parsed_string = parser.parse(str.assign("asd kcj 823 823 3 "));
    assert(token_count == 2);
    assert((parsed_string == vector<string>{"asd", "kcj", "823", "823", "3"}));

    token_count = 0;
    parser.addOnStartCallback([&token_count]() { token_count += 100; });
    parser.addOnEndCallback([&token_count]() { token_count *= -3; });
    parser.parse(str.assign("-3 asdv i88 823 abc 823 a b c"));
    assert(token_count == -309);

    cout << "Tests passed!" << endl;
    return EXIT_SUCCESS;
}
