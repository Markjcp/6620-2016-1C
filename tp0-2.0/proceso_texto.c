#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <proceso_texto.h>
#include <cola.h>


 /*******************************************************************
 *                DEFINICION DE CONSTANTES
 ******************************************************************/
 #define IGUALES 0
 #define POS_INICIAL 0
 #define FIN_STRING '\0'
 #define FIN_PALABRA ' '
 #define TAMANIO_INICIAL_BUFFER 12
 
  /*******************************************************************
 *                        IMPLEMENTACION
 ******************************************************************/
cola_t *separar_linea(char *linea)
//Recibe un string de numeros y devuelve una cola con todos esos numeros dobles como memoria dinamica
{
	cola_t *cola = cola_crear();
	if (!cola) return NULL;
	size_t pos_linea = POS_INICIAL;
	size_t pos_palabra;
	size_t largo = TAMANIO_INICIAL_BUFFER;
	bool ok_palabra;
	char *ptr;
	while(linea[pos_linea] != FIN_STRING)
	{
		char* buffer = malloc(sizeof(char)*(largo));
		pos_palabra = POS_INICIAL;
		while( (linea[pos_linea] != FIN_STRING) && (ok_palabra = (linea[pos_linea] != FIN_PALABRA)) )
		{
			if (pos_palabra == largo-2)
			{
				largo += largo;
				char *buffer_aux = realloc(buffer, largo * sizeof(char));
				if (!buffer_aux)
					return cola;                 // Si no funciona la redimensión, corto aca
				buffer = buffer_aux;					
			}
			buffer[pos_palabra++] = linea[pos_linea++];
		}
		buffer[pos_palabra] = FIN_STRING;
		if(!ok_palabra)
		{
			pos_linea++;
			largo = TAMANIO_INICIAL_BUFFER;
		}
		double *num = malloc(sizeof(double));
		*num = strtod(buffer,&ptr);
		if (*ptr != FIN_STRING)
		{
			fprintf(stderr,"ERROR: El string '%s' recibido contiene '%s' que no se puede interpretar como numero y será omitido \n", buffer, ptr);
			free(num);
		}
		else
		{
			cola_encolar(cola,num);	
		}
		free(buffer);		
	}
	return cola;
}
