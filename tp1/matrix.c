#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <matrix.h>
#include <print_string.h>

double double_at(matrix_t* m, size_t i, size_t j){
	return (double)*(m->array+(i*m->cols+j));
}

void load_value(matrix_t* m, size_t i, size_t j, double value){
	m->array[i*m->cols+j]=value;

}

matrix_t* create_matrix(size_t rows, size_t cols){
	matrix_t* matrix = (matrix_t*)malloc(sizeof(matrix_t));
	if (!matrix){
		return NULL;
	}
	matrix->rows = rows;
	matrix->cols = cols;
	size_t array_size = sizeof(double)*(matrix->cols)*(matrix->rows);
	matrix->array = (double*)malloc(array_size);
	if (!matrix->array){
	    free(matrix);  
	    return NULL;
	}
	return matrix;
}

int print_matrix(FILE* fp, matrix_t* m){
	size_t i;
	size_t j;
	int fd;
	size_t tam_buffer = TAMANIO_BUFFER;
	size_t tam_salida = 4*tam_buffer;
	char* aux;
	char* num = malloc(tam_buffer*sizeof(char));
	if (!num) return ERROR_ESCRITURA;
	char* salida = malloc(tam_salida*sizeof(char));
	if (!salida)
	{
		free(num);
		return ERROR_ESCRITURA;
	}
	fd = fileno(fp);
	if (fd == -1)
	{
		free(num);
		free(salida);
		return ERROR_ESCRITURA;
	} 
	if(sprintf(salida,"%d ",(int)m->rows) < 0) return ERROR_ESCRITURA;
	for ( i = 0; i < m->rows; i++) 
	{
		for ( j = 0; j < m->cols; j++) 
		{
			if (2*strlen(salida) >= tam_salida)
			{
				tam_salida += tam_salida;
				aux = realloc(salida, tam_salida * sizeof(char));
				if (!aux)
				{
					free(num);
					free(salida);
					return ERROR_ESCRITURA;
				}
				salida = aux;
			}  			
			if(sprintf(num,"%.1f ", double_at(m,i,j)) < 0)
			{
				free(num);
				free(salida);
				return ERROR_ESCRITURA;
			}
			strcat(salida, num);
		}
	}
	free(num);
	strcat(salida, "\n");
	print_string(fd, salida);
	free(salida);
	return 0;
}

int print_matrix_std_o(matrix_t* m) {
	size_t i = 0;
	size_t j = 0;
	for (; i < m->rows; i++) {
		for (j=0; j < m->cols; j++) {
			if(printf("%f ", double_at(m,i,j)) < 0){
			    return ERROR_ESCRITURA;
			}
		}
		if(printf("\n") < 0){
		  return ERROR_ESCRITURA;
		}
	}
	return 0;
}

void destroy_matrix(matrix_t* m){
	free(m->array);
	free(m);
}
