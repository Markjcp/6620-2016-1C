#include <stdio.h>
#include <stdlib.h>
#include <matrix.c>

int main(void) {
	matrix_t* m = create_matrix(2,2);
	load_value(m,0,0,1.0);
	load_value(m,0,1,2.0);
	load_value(m,1,0,3.0);
	load_value(m,1,1,4.0);
	print_matrix_std_o(m);
	destroy_matrix(m);
	return EXIT_SUCCESS;
}
