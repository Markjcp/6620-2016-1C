#include <stdio.h>
#include <stdlib.h>
#include <lectura.h>
#define FIN_LINEA '\n'
#define FIN_STRING '\0'
#define TAMANIO_INICIAL_BUFFER 10


char* leer_linea(){
	int c;
	char ch;	
	size_t tam = TAMANIO_INICIAL_BUFFER; 
	int i;

	char* buffer = malloc(sizeof(char)*(tam));
	if (!buffer) return NULL;
	c = getchar();
	ch = c;
	for(i = 0; ch != FIN_LINEA ; i++){ //leo hasta el enter
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

		buffer[i] = ch;
		c = getchar();
		ch = c;
	}
	buffer[i] = FIN_STRING; // es necesario cerrar el string
	return buffer;
}
