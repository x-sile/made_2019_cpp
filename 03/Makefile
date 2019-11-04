CC=g++ -std=c++14

all: test

test: test.o parser.o
	$(CC) -o test test.o parser.o
	./test

parser.o: parser.cpp parser.h
	$(CC) -c parser.cpp

test.o: test.cpp parser.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test