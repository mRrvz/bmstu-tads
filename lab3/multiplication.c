#include <string.h>
#include <stdio.h>

#include "multiplication.h"
#include "processing.h"
#include "matrix_memory_manager.h"
#include "matrix_struct.h"
#include "list_operations.h"

void std_multiplication(std_matrix_t *matrix, std_matrix_t *vector, std_matrix_t *result)
{
    for (int i = 0; i < matrix->ysize; i++)
    {
        for (int j = 0; j < matrix->xsize; j++)
        {
            result->matrix[0][i] += matrix->matrix[i][j] * vector->matrix[0][j];
        }
    }
}

void sparce_multiplication(matrix_t *matrix, std_matrix_t *vector, matrix_t *result)
{
    int k, curr_sum;
    node_t *temp_IA = get_by_pos(&matrix->IA, 0);
    node_t *temp_IA_next = NULL;
    result->curr_size = 0;

    for (int i = 0; i < matrix->ysize - 1; i++)
    {
        temp_IA_next = temp_IA->next_element;
        curr_sum = 0;

        for (int j = temp_IA->start_column_ind; j < temp_IA_next->start_column_ind; j++)
        {
            curr_sum += matrix->A[j] * vector->matrix[0][matrix->JA[j]];
        }

        if (curr_sum != 0)
        {
            result->A[result->curr_size] = curr_sum;
            result->JA[result->curr_size] = i;
            result->curr_size++;
        }

        temp_IA = temp_IA_next;
        k = temp_IA->start_column_ind;
    }

    curr_sum = 0;
    for (int i = k; i < matrix->curr_size; i++)
    {
        curr_sum += matrix->A[i] * vector->matrix[0][matrix->JA[i]];
    }

    if (curr_sum != 0)
    {
        result->A[result->curr_size] = curr_sum;
        result->JA[result->curr_size] = matrix->ysize - 1;
        result->curr_size++;
    }
}

static void transpose_matrix(std_matrix_t *matrix, std_matrix_t *new_matrix)
{
    for (int i = 0; i < matrix->ysize; i++)
    {
        for (int j = 0; j < matrix->xsize; j++)
        {
            *(*(new_matrix->matrix + j) + i) = *(*(matrix->matrix + i) + j);
        }
    }
}

void transpose(std_matrix_t *matrix)
{
    std_matrix_t new_matrix_temp;
    new_matrix_temp.xsize = matrix->ysize;
    new_matrix_temp.ysize = matrix->xsize;

    new_matrix(&new_matrix_temp);
    transpose_matrix(matrix, &new_matrix_temp);

    free_memory(matrix);
    *matrix = new_matrix_temp;
}
