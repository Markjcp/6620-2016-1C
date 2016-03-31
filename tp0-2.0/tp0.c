#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "lectura.h"
#include "proceso_texto.h"
#include "cola.h"

void imprimirAyuda(){
    printf("Usage: \n");
    printf("\t tp0 -h \n");
    printf("\t tp0 <in_file> out_file \n");
    printf("Options: \n");
    printf("\t -h, --help \n");
    printf("Examples: \n");
    printf("\t cat in.txt | tp0 > out.txt \n");
}

void cargar_matriz(matrix_t* m, cola_t* cola_num, size_t tam_matriz){
	double* num;
	size_t i;
	size_t j;
	for (i=0; i < tam_matriz; i++)
	{
		for (j=0; j< tam_matriz; j++)
		{
			num = cola_desencolar(cola_num);
 			load_value(m, i, j, *num);
 			free(num);
		}
 		
 	}
}

int main(int argc, char **argv)
{
	if((argc == 2) && (strcmp(argv[1],"-h") == 0))
	{
	    imprimirAyuda();
	    return 0;
	}
	size_t cant_numeros;
	size_t tam_matrices;
	size_t cant_elem_matriz;
	double *num;
	matrix_t* m1;
	matrix_t* m2;
	matrix_t* m3;
	cola_t *cola_numeros;
	char *linea = leer_linea();
 	while (linea) //Es NULL cuando hay error en memoria o se llegó al EOF
 	{
 		cola_numeros = separar_linea(linea);
 		cant_numeros = cola_tamanio(cola_numeros);
 		if (!cola_esta_vacia(cola_numeros))
 		{
 			num = cola_desencolar(cola_numeros);
 			tam_matrices = (size_t)*num;
 			free(num);
 			cant_elem_matriz = tam_matrices*tam_matrices;	
 		}
 		else
 		{
 			fprintf(stderr, "ERROR: La linea ingresada está vacía\n");
 			cola_destruir(cola_numeros,NULL);
 			free(linea);
 			linea = leer_linea();
 			continue;
 		}
 		if ( (cant_numeros - 1) != (cant_elem_matriz*2) ) //Validacion
 		{ 
 			fprintf(stderr, "ERROR: El tamaño de las matrices provisto es incorrecto o faltaron datos de las mismas\n");
 			cola_destruir(cola_numeros,free);
 			free(linea);
 			linea = leer_linea();
 			continue;
 		}
 		m1 = create_matrix(tam_matrices, tam_matrices);
 		cargar_matriz(m1, cola_numeros, tam_matrices);
 		m2 = create_matrix(tam_matrices, tam_matrices);
 		cargar_matriz(m2, cola_numeros, tam_matrices);
 		m3 = matrix_multiply(m1, m2);
 		print_matrix(stdout, m3);

 		cola_destruir(cola_numeros,free);
 		destroy_matrix(m1);
 		destroy_matrix(m2);
 		destroy_matrix(m3);
 		free(linea);
		linea = leer_linea();
 	}
	return 0;
}