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
	printf("\n%s: %s\n", name, result? "OK" : "ERROR");
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/


/* Prueba que las primitivas del abb funcionen correctamente. */
void test_print_basico()
{
	ssize_t result;
	result = print_string(1,"OK");
	print_test("Se imprimieron 2 bytes", result == 2);
	
	result = print_string(1," ");
        print_test("Se imprimio 1 byte", result == 1);
	
	result = print_string(1,"");
	print_test("Se imprimieron 0 bytes", result == 0);
	
	result = print_string(1,"Linea 1 \nLinea 2");
	print_test("Se imprimieron 16 bytes",result == 16);
	
	result = print_string(1,"N""\xa3""mero");
	print_test("Se imprimieron 6 bytes",result == 6);
}

void test_error_fd()
{
	ssize_t result;
	result = print_string(34,"OK\n");
	print_test("Al utilizar un file descriptor incorrecto obtengo error", result == -1);
}

void test_volumen()
{
	ssize_t result;
	size_t i;
	for(i = 0; i < 10000; i++)
	{
		result = print_string(1,"OK\n");	
		if (result < 0) break;
	}
	
	print_test("La prueba de impresion de volumen fue correcta", result > -1);	
}
	
/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

/* Programa principal. */
int main(int argc, char** argv)
{

	
	/* Ejecuta todas las pruebas unitarias. */
	test_print_basico();
	test_error_fd();
	test_volumen();
	
	return 0;
}
