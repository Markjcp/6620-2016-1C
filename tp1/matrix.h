#ifndef MATRIX_H_
#define MATRIX_H_
#define ERROR_ESCRITURA -1

#include <stdlib.h>

typedef struct matrix {
	size_t rows;
	size_t cols;
	double* array;
} matrix_t;

matrix_t* create_matrix(size_t rows, size_t cols);

int print_matrix(FILE* fp, matrix_t* m);

int print_matrix_std_o(matrix_t* m);

void destroy_matrix(matrix_t* m);

void load_value(matrix_t* m, size_t i, size_t j, double value);

double double_at(matrix_t* m, size_t i, size_t j);

#endif /* MATRIX_H_ */
