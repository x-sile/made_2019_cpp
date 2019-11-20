#include "serializer.h"
#include "deserializer.h"
#include <iostream>
#include <sstream>
#include <cassert>

struct Data1 {
    uint64_t a;
    bool b;
    uint64_t c;

    template<class Serializer>
    Error serialize(Serializer &serializer) {
        return serializer(a, b, c);
    }
};

struct Data2 {
    bool a;
    bool b;

    template<class Serializer>
    Error serialize(Serializer &serializer) {
        return serializer(a, b);
    }
};

struct Data3 {
    uint64_t a;

    template<class Serializer>
    Error serialize(Serializer &serializer) {
        return serializer(a);
    }
};


void test1() {
    Data1 x{1, true, 2};
    Data1 y{0, false, 0};
    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void test2() {
    Data2 x{false, true};
    Data2 y{true, false};
    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
}

void test3() {
    Data3 x{1233};
    Data3 y{1};
    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);
    assert(x.a == y.a);
}

void test4() {
    Data3 x{1233};
    Data3 y{0};
    std::stringstream stream;

    stream << "corrupted" << std::endl;

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::CorruptedArchive);
    assert(x.a != y.a);
}

int main() {
    test1();
    test2();
    test3();
    test4();
    std::cout << "Tests passed!" << std::endl;
    return EXIT_SUCCESS;
}
