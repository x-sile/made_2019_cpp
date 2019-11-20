CC=g++ -std=c++14

all: test

test: test.o
	$(CC) -o test test.o
	./test

test.o: test.cpp serializer.h deserializer.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
