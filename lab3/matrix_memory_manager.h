#ifndef __MATRIX_MEMORY_MANAGER_H__
#define __MATRIX_MEMORY_MANAGER_H__

#include "matrix_struct.h"

int new_matrix(std_matrix_t *const matrix);

void free_memory(std_matrix_t *const matrix);

void free_std_matrix(std_matrix_t *matrix, std_matrix_t *vector, std_matrix_t *result);

void free_all_memory(list_t *list_matrix, list_t *list_vector, list_t *list_result,
    std_matrix_t *std_matrix, std_matrix_t *std_vector, std_matrix_t *std_result);

#endif
