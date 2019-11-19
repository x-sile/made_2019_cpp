CC=g++ -std=c++14

all: test

test: test.o bigint.o
	$(CC) -o test test.o bigint.o
	./test

test.o: test.cpp bigint.h
	$(CC) -c test.cpp

bigint.o: bigint.cpp bigint.h
	$(CC) -c test.cpp bigint.cpp

clean:
	rm -rf *.o test
