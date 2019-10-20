CC=g++ -std=c++14

all: test

test: test.o allocator.o
	$(CC) -o test test.o allocator.o
	./test

allocator.o: allocator.cpp
	$(CC) -c allocator.cpp

test.o: test.cpp allocator.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test