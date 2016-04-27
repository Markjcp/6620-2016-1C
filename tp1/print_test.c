#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <print_string.h>

/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
	printf("%s: %s\n", name, result? "OK" : "ERROR");
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/


/* Prueba que las primitivas del abb funcionen correctamente. */
void prueba_print_basico()
{
	ssize_t result;
	result = print_string(1,"OK");
	print_test("Se imprimieron dos bytes", result == 2);
}
	
/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

/* Programa principal. */
int main(int argc, char** argv)
{

	
	/* Ejecuta todas las pruebas unitarias. */
	prueba_print_basico();
	
	return 0;
}
