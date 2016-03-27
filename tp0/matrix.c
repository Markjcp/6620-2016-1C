#include <matrix.h>
#include <stdio.h>
#include <stdlib.h>

matrix_t* create_matrix(size_t rows, size_t cols){
	matrix_t* matrix = (matrix_t*)malloc(sizeof(matrix_t));
	matrix->rows = rows;
	matrix->cols = cols;
	return matrix;
}

int print_matrix(FILE* fp, matrix_t* m){
	printf("print_matrix");
}

matrix_t* matrix_multiply(matrix_t* m1, matrix_t* m2){
	matrix_t* res = (matrix_t*)malloc(sizeof(matrix_t));
/*	for (int x = 0; x < m1->rows; ++x) {

	}*/
	return res;
}

void destroy_matrix(matrix_t* m){
	free(m);
}


