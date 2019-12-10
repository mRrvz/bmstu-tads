#include <stdlib.h>

#include "matrix_memory_manager.h"
#include "matrix_struct.h"
#include "errors.h"
#include "list_operations.h"

int new_matrix(std_matrix_t *const matrix)
{
    matrix->matrix = malloc(matrix->ysize * sizeof(int *));

    if (matrix->matrix == NULL)
    {
        return MEMORY_ERROR;
    }

    for (unsigned i = 0; i < matrix->ysize; i++)
    {
        *(matrix->matrix + i) = malloc(matrix->xsize * sizeof(int));

        if (*(matrix->matrix + i) == NULL)
        {
            return MEMORY_ERROR;
        }
    }

    return OK;
}

void free_memory(std_matrix_t *const matrix)
{
    for (unsigned i = 0; i < matrix->ysize; i++)
    {
        free(matrix->matrix[i]);
        matrix->matrix[i] = NULL;
    }

    free(matrix->matrix);
    matrix->matrix = NULL;
}

void free_std_matrix(std_matrix_t *matrix, std_matrix_t *vector, std_matrix_t *result)
{
    free_memory(matrix);
    free_memory(vector);
    free_memory(result);
}

void free_all_memory(list_t *list_matrix, list_t *list_vector, list_t *list_result,
     std_matrix_t *std_matrix, std_matrix_t *std_vector, std_matrix_t *std_result)
{
    free_list(list_matrix);
    free_list(list_vector);
    free_list(list_result);
    free_std_matrix(std_matrix, std_vector, std_result);
}
