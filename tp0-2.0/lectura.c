#include <stdio.h>
#include <stdlib.h>
#include <lectura.h>
#define TAMANIO_INICIAL_BUFFER 10
#define FIN_LINEA '\n'
#define FIN_STRING '\0'


char* leer_linea(){
	char c;	
	size_t tam = TAMANIO_INICIAL_BUFFER; 
	int i;

	char* buffer = malloc(sizeof(char)*(tam));
	if (!buffer) return NULL;
	c = getchar();
	for(i = 0; c != FIN_LINEA ; i++){ //leo hasta el enter
		if (c == EOF)
		{	
			free(buffer);
			return NULL;
		}
		if(i + 1 == tam){ // si llego al tamanio de mi cadena
			tam += tam;  // la forma de modificar tam es arbitraria
			char* aux = realloc(buffer, tam * sizeof(char));
			if(!aux) return NULL;  // si falla realloc, termino aca
			buffer = aux;
		}

		buffer[i] = c;
		c = getchar();
	}
	buffer[i] = FIN_STRING; // es necesario cerrar el string
	return buffer;
}
