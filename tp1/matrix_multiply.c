#include <stdio.h>
#include <stdlib.h>
#include <matrix.h>
#include <matrix_multiply.h>

void matrix_multiply(matrix_t* m1, matrix_t* m2, matrix_t* result) {
	size_t i = 0;
	size_t j = 0;
	double aux = 0.0;
	size_t x;
	for (; i < m1->rows; i++) {
		for (j = 0; j < m1->cols; j++) {
			aux = 0.0;
			for(x=0; x<m1->cols;x++){
				double first = double_at(m1,i,x);
				double second = double_at(m2,x,j);
				aux += (first*second);
			}
			load_value(result,i,j,aux);
		}
	}
}
