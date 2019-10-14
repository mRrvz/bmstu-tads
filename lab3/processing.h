#ifndef __PROCESSING_H__
#define __PROCESSING_H__

#include "matrix_struct.h"

void init_sizes(matrix_t *const vector, const int xsize);

int init_sparce_matrix(matrix_t *const sparce_matrix, int *const A, int *const IA, list_t *list);

int init_std_matrix(std_matrix_t *const matrix, const int xsize, const int ysize);

int filling_matrix(std_matrix_t *std_matrix, matrix_t *sparce_matrix,
    const bool enter_type, const bool mv_type);

void copy_matrix(std_matrix_t std_matrix, matrix_t *sparce_matrix);

#endif
