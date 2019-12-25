CC=g++ -std=c++14 -pthread

all: test

test: test.o
	$(CC) -o test test.o
	./test

test.o: test.cpp threadpull.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
