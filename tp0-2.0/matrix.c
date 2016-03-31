#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

double double_at(matrix_t* m, size_t i, size_t j){
	return (double)*(m->array+(i*m->cols+j));
}

void load_value(matrix_t* m, size_t i, size_t j, double value){
	m->array[i*m->cols+j]=value;

}

matrix_t* create_matrix(size_t rows, size_t cols){
	matrix_t* matrix = (matrix_t*)malloc(sizeof(matrix_t));
	matrix->rows = rows;
	matrix->cols = cols;
	size_t array_size = sizeof(double)*(matrix->cols)*(matrix->rows);
	matrix->array = (double*)malloc(array_size);
	return matrix;
}

int print_matrix(FILE* fp, matrix_t* m){
	size_t i;
	size_t j;
	fprintf(fp,"%d ",m->rows);
	for ( i = 0; i < m->rows; i++) 
	{
		for ( j = 0; j < m->cols; j++) 
		{
			fprintf(fp,"%.1f ", double_at(m,i,j));
		}
	}
	fprintf(fp,"\n");
	return 0;
}

matrix_t* matrix_multiply(matrix_t* m1, matrix_t* m2) {
	matrix_t* result = create_matrix(m1->rows, m2->cols);
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
	return result;
}

void destroy_matrix(matrix_t* m){
	free(m->array);
	free(m);
}