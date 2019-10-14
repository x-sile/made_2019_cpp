CC=g++ -std=c++14

all: run test

run: run.o parser.o
	$(CC) -o run run.o parser.o

test: test.o parser.o
	$(CC) -o test test.o parser.o
	./test

run.o: run.cpp parser.h
	$(CC) -c run.cpp

test.o: test.cpp parser.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o run test