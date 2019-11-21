CC=g++ -std=c++14

all: test

test: test.o string_format.o
	$(CC) -o test test.o string_format.o
	./test

string_format.o: string_format.cpp string_format.h
	$(CC) -c string_format.cpp

test.o: test.cpp string_format.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
