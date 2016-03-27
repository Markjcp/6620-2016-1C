CC = gcc
CFLAGS = -c -g -Wall -I ./
PROG = tp0
DEFAULT = all

main: matrix.c tp0.cpp matrix.h 
	$(CC) $(CFLAGS) matrix.c tp0.cpp

all: main
	$(CC) tp0.o -o $(PROG)
	
clean:
	rm -rf *.o $(PROG)