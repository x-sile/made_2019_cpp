#include "vector.h"

#include <iostream>
#include <cassert>

int main() {
    vector<std::string> vec;
    assert(vec.empty());
    assert(vec.capacity() == 8);

    vector<std::string> vec2(5);
    assert(vec2.empty());
    assert(vec2.capacity() == 5);

    vector<std::string> vec3{5, "5"};
    assert(vec3.size() == 5);
    assert(vec3.capacity() == 5);

    vector<int> vec4{1, 2, 3};
    assert(vec4.size() == 3);
    assert(vec4.capacity() == 3);

    std::string tmp = "4";
    vec.push_back(tmp);
    assert(vec[0] == "4");
    vec.push_back("5");
    assert(vec[1] == "5");
    assert(vec.size() == 2);
    assert(vec.capacity() == 8);
    vec.pop_back();
    assert(vec.size() == 1);
    assert(vec.capacity() == 8);
    for (int i = 0; i < 10; i++) {
        vec.push_back("1");
    }
    assert(vec.size() == 11);
    assert(vec.capacity() == 16);
    vec.resize(32);
    assert(vec.size() == 11);
    assert(vec.capacity() == 32);
    vec.resize(48, "10");
    assert(vec.size() == 11);
    assert(vec.capacity() == 48);
    assert(vec[35] == "10");
    vec.resize(5);
    assert(vec.size() == 5);
    assert(vec.capacity() == 5);
    vec.reserve(15);
    assert(vec.capacity() == 15);
    vec.clear();
    assert(vec.empty());
    assert(vec.capacity() == 15);

    assert(vec.end() == vec.begin());
    assert(vec.rbegin() == vec.rend());
    for (int i = 0; i < 10; i++) {
        vec.push_back("999");
    }
    auto beg_iter = vec.begin();
    auto end_iter = vec.end();
    assert(beg_iter != end_iter);
    assert(beg_iter < end_iter);
    assert(beg_iter + 10 == end_iter);
    beg_iter++;
    assert(beg_iter + 9 == end_iter);
    --end_iter;
    assert(beg_iter + 8 == end_iter);
    beg_iter += 8;
    assert(beg_iter == end_iter);

    vec3 = vec;
    assert(vec3[9] == vec[9]);

    std::cout << "Tests passed!" << std::endl;
    return EXIT_SUCCESS;
}
