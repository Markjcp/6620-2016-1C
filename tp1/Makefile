CC = gcc
CFLAGS = -c -g -Wall -I ./
PROG = tp1
DEFAULT = all

main: matrix.h cola.h proceso_texto.h lectura.h cola.c matrix.c proceso_texto.c lectura.c tp1.c 
	$(CC) $(CFLAGS) cola.c proceso_texto.c lectura.c matrix.c tp1.c
	
multiply_c: matrix_multiply.h matrix_multiply.c
	$(CC) $(CFLAGS) matrix_multiply.c
	
multiply_mips: matrix_multiply.S
	$(CC) $(CFLAGS) matrix_multiply.S

print_mips: print_string.S
	$(CC) $(CFLAGS) print_string.S
	
main_tests: matrix.h matrix_multiply.h matrix.c matrix_multiply.c *test.c
	$(CC) $(CFLAGS) matrix.c matrix_multiply.c *_test.c

all: multiply_c print_mips main
	$(CC) cola.o proceso_texto.o lectura.o matrix.o matrix_multiply.o print_string.o tp1.o -o $(PROG)
	
mips: multiply_mips print_mips main
	$(CC) cola.o proceso_texto.o lectura.o matrix.o matrix_multiply.o print_string.o tp1.o -o $(PROG)
	
test: main_tests
	$(CC) basic_test.o matrix.o matrix_multiply.o -o basic_test
	$(CC) multiply_test.o matrix.o matrix_multiply.o -o multiply_test
	
clean:
	rm -rf *.o $(PROG) basic_test multiply_test