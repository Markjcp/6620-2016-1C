CC = gcc
CFLAGS = -c -g -Wall -I ./
PROG = tp1
DEFAULT = all

main: matrix.h cola.h proceso_texto.h lectura.h cola.c matrix.c proceso_texto.c lectura.c tp1.c 
	$(CC) $(CFLAGS) cola.c proceso_texto.c lectura.c matrix.c tp1.c
	
main_tests: matrix.h matrix.c *test.c
	$(CC) $(CFLAGS) matrix.c *_test.c

all: main
	$(CC) cola.o proceso_texto.o lectura.o matrix.o tp1.o -o $(PROG)
	
test: main_tests
	$(CC) basic_test.o matrix.o -o basic_test
	$(CC) multiply_test.o matrix.o -o multiply_test
	
clean:
	rm -rf *.o $(PROG) basic_test multiply_test