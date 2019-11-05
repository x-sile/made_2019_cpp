CC=g++ -std=c++14

all: test

test: test.o matrix.o
	$(CC) -o test test.o matrix.o
	./test

matrix.o: matrix.cpp
	$(CC) -c matrix.cpp

test.o: test.cpp matrix.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
