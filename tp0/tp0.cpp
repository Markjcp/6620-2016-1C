#include <stdio.h>
#include <stdlib.h>
#include <matrix.c>

int main(void) {
	puts("hellooooooooooo");
	matrix_t* m = create_matrix(2,2);
	destroy_matrix(m);
	return EXIT_SUCCESS;
}
