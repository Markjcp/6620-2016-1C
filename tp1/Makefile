CC = gcc
CFLAGS = -c -g -Wall -I ./
PROG = tp1
DEFAULT = all

main: matrix.h matrix_multiply.h cola.h proceso_texto.h lectura.h cola.c matrix.c matrix_multiply.c proceso_texto.c lectura.c tp1.c 
	$(CC) $(CFLAGS) cola.c proceso_texto.c lectura.c matrix.c matrix_multiply.c tp1.c
	
main_tests: matrix.h matrix_multiply.h matrix.c matrix_multiply.c *test.c
	$(CC) $(CFLAGS) matrix.c matrix_multiply.c *_test.c

all: main
	$(CC) cola.o proceso_texto.o lectura.o matrix.o matrix_multiply.o tp1.o -o $(PROG)
	
test: main_tests
	$(CC) basic_test.o matrix.o matrix_multiply.o -o basic_test
	$(CC) multiply_test.o matrix.o matrix_multiply.o -o multiply_test
	
clean:
	rm -rf *.o $(PROG) basic_test multiply_test