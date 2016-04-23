#include <stdio.h>
#include <stdlib.h>
#include <matrix.h>
#include <matrix_multiply.h>

int main(void) {
	matrix_t* m = create_matrix(3, 3);
	load_value(m, 0, 0, 1.0);
	load_value(m, 0, 1, 2.0);
	load_value(m, 0, 2, 3.0);
	load_value(m, 1, 0, 4.0);
	load_value(m, 1, 1, 5.0);
	load_value(m, 1, 2, 6.1);
	load_value(m, 2, 0, 3.0);
	load_value(m, 2, 1, 2.0);
	load_value(m, 2, 2, 1.0);

	matrix_t* m1 = create_matrix(3, 3);
	load_value(m1, 0, 0, 1.0);
	load_value(m1, 0, 1, 0.0);
	load_value(m1, 0, 2, 0.0);
	load_value(m1, 1, 0, 0.0);
	load_value(m1, 1, 1, 1.0);
	load_value(m1, 1, 2, 0.0);
	load_value(m1, 2, 0, 0.0);
	load_value(m1, 2, 1, 0.0);
	load_value(m1, 2, 2, 1.0);


	print_matrix_std_o(m);
	printf("\n");
	print_matrix_std_o(m1);
	printf("\n");

	matrix_t* result = matrix_multiply(m, m1);
	print_matrix_std_o(result);

	destroy_matrix(m);

	destroy_matrix(m1);
	destroy_matrix(result);
	return EXIT_SUCCESS;
}
