#ifndef __PRINT_H__
#define __PRINT_H__

#include "matrix_struct.h"

void initial_print();

void print_multiplication_results(const std_matrix_t std_matrix);

void print_compare_results(std_matrix_t std_matrix, matrix_t sparce_matrix,
    int64_t std_start, int64_t std_end, int64_t sparce_end, int curr_size);

void random_matrix_print(std_matrix_t matrix, std_matrix_t vector);

void sparce_matrix_print(const matrix_t matrix);

#endif
