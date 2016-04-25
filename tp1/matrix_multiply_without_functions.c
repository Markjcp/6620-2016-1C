#include <stdio.h>
#include <stdlib.h>
#include <matrix.h>
#include <matrix_multiply.h>

void matrix_multiply(matrix_t* m1, matrix_t* m2, matrix_t* result) {
	size_t i = 0;
	size_t j = 0;
	size_t x;
	size_t rows = m1->rows;
	size_t cols = m1->cols;
	size_t aux1;
	size_t aux2;
	size_t aux3;
	double aux = 0.0;
	double first;
	double second;
	for (; i < m1->rows; i++) {
		for (j = 0; j < m1->cols; j++) {
			aux = 0.0;
			for(x=0; x<m1->cols;x++){
				aux1 = i*m1->cols;
				aux2 = aux1 + x;
				aux3 = m1->array+aux2;
				first = (double)*(aux3);
				aux1 = x*m2->cols;
				aux2 = aux1 + j;
				aux3 = m2->array+aux2;
				second = (double)*(aux3);
				aux += (first*second);
			}
			load_value(result,i,j,aux);
			aux1 = i*result->cols;
			aux1 += j;
			result->array[aux1]=aux;
	}
}
