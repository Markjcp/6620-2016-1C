CC = gcc
CFLAGS = -c -g -Wall -I ./
PROG = tp0
DEFAULT = all

main: matrix.c tp0.cpp matrix.h 
	$(CC) $(CFLAGS) matrix.c tp0.cpp
	
main_tests: matrix.c *_test.cpp matrix.h
	$(CC) $(CFLAGS) matrix.c *_test.cpp

all: main
	$(CC) tp0.o -o $(PROG)
	
test: main_tests
	$(CC) basic_test.o -o basic_test
	$(CC) multiply_test.o -o multiply_test
	
clean:
	rm -rf *.o $(PROG) basic_test multiply_test