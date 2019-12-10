#ifndef __READ_H__
#define __READ_H__

#include "matrix_struct.h"

int read_sizes(matrix_t *matrix, matrix_t *vector);

int read_type(bool *enter_type);

int read_matrix(std_matrix_t *std_matrix, const int maxsize);

int read_vector(std_matrix_t *std_matrix, const int maxsize);

#endif
