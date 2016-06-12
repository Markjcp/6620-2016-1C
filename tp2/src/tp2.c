#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cola.h>
#include <matrix.h>
#include <lectura.h>
#include <time.h>
#include <proceso_texto.h>

#define BILLION 1E9

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

double calcular_tiempo(struct timespec *ti, struct timespec *tf){
	double time_elapsed = ( tf->tv_sec - ti->tv_sec ) + ( tf->tv_nsec - ti->tv_nsec ) / BILLION;
	return time_elapsed;
}

int main(int argc, char **argv)
{
	if((argc == 2) && (strcmp(argv[1],"-h") == 0))
	{
	    imprimirAyuda();
	    return 0;
	}
	struct timespec lineStart,lineEnd,multiplyStart,multiplyEnd;
	size_t cant_numeros;
	size_t tam_matrices;
	size_t cant_elem_matriz;
	size_t bs;
	double *num;
	matrix_t* m1;
	matrix_t* m2;
	matrix_t* m3;
	cola_t *cola_numeros;

	clock_gettime(CLOCK_REALTIME, &lineStart);
	char *linea = leer_linea();
	if(!linea){
	   fprintf(stderr, "ERROR DE MEMORIA: No se pudo leer la linea de entrada\n");
	   exit(-1);
	}
 	while (linea) //Es NULL cuando hay error en memoria o se llegó al EOF
 	{
 		cola_numeros = separar_linea(linea);
 		if (!cola_numeros)
 		{
 			fprintf(stderr, "ERROR DE MEMORIA: No se pudo procesar la línea de entrada\n");
 			free(linea);
 			exit(-1);
 		}
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
 		if(!m1){
 			fprintf(stderr, "ERROR DE MEMORIA: No se pudo crear la matriz de entrada\n");
 			cola_destruir(cola_numeros,free);
 			free(linea);
 			exit(-2);
 		}
 		cargar_matriz(m1, cola_numeros, tam_matrices);
 		m2 = create_matrix(tam_matrices, tam_matrices);
 		if(!m2){
 			fprintf(stderr, "ERROR DE MEMORIA: No se pudo crear la matriz de entrada\n");
 		 	destroy_matrix(m1);
 		 	cola_destruir(cola_numeros,free);
 		 	free(linea);
 		 	exit(-2);
 		}
 		cargar_matriz(m2, cola_numeros, tam_matrices);
 		m3 = create_matrix(tam_matrices, tam_matrices);
		if (!m3) {
			fprintf(stderr, "ERROR DE MEMORIA: No se pudo crear la matriz de salida\n");
			destroy_matrix(m1);
 			destroy_matrix(m2);
			cola_destruir(cola_numeros, free);
			free(linea);
			exit(-3);
		}
		matrix_initialize(m3);
		bs = 8; //Valor de blocking
		clock_gettime(CLOCK_REALTIME, &multiplyStart);
 		matrix_multiply(m1, m2, m3, bs);
 		clock_gettime(CLOCK_REALTIME, &multiplyEnd);
 		if(print_matrix(stdout, m3) < 0){
		    fprintf(stderr, "ERROR I/O: No se pudo escribir la salida\n");
		    destroy_matrix(m1);
 			destroy_matrix(m2);
 			destroy_matrix(m3);
		    cola_destruir(cola_numeros, free);
		    free(linea);
		    exit(-4);
		}
		clock_gettime(CLOCK_REALTIME, &lineEnd);
		printf( "Tiempo de proceso de linea(s): %lf\n", calcular_tiempo(&lineStart,&lineEnd) );
		printf( "Tiempo de matrix_multiply(s): %lf\n", calcular_tiempo(&multiplyStart,&multiplyEnd) );
 		cola_destruir(cola_numeros,free);
 		destroy_matrix(m1);
 		destroy_matrix(m2);
 		destroy_matrix(m3);
 		free(linea);
 		clock_gettime(CLOCK_REALTIME, &lineStart);
		linea = leer_linea();
 	}
	return 0;
}
