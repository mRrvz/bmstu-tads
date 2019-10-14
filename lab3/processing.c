#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "processing.h"
#include "matrix_struct.h"
#include "errors.h"
#include "read.h"
#include "matrix_memory_manager.h"
#include "multiplication.h"
#include "list_struct.h"
#include "list_operations.h"

void init_sizes(matrix_t *const vector, const int xsize)
{
    vector->xsize = xsize;
    vector->ysize = 1;
}

int init_sparce_matrix(matrix_t *const sparce_matrix, int *const A, int *const JA, list_t *list)
{
    int code_error;

    if (sparce_matrix->ysize != 1)
    {
        if ((code_error = init_list_ptrs(sparce_matrix->xsize, list)))
        {
            free_list(list);
            return code_error;
        }
    }
    else
    {
        list->ptr = NULL;
    }

    sparce_matrix->A = A;
    sparce_matrix->JA = JA;
    sparce_matrix->IA = *list;

    return OK;
}

int init_std_matrix(std_matrix_t *const matrix, const int xsize, const int ysize)
{
    int code_error;

    matrix->xsize = xsize;
    matrix->ysize = ysize;

    if ((code_error = new_matrix(matrix)))
    {
        return code_error;
    }

    return OK;
}

static void random_filling(std_matrix_t *const std_matrix, const int maxsize)
{
    srand(time(NULL));

    for (int i = 0; i < maxsize; i++)
    {
        int irand = 0;
        int jrand = 0;
        do
        {
            irand = rand() % std_matrix->ysize;
            jrand = rand() % std_matrix->xsize;
        } while (std_matrix->matrix[irand][jrand] != 0);

        std_matrix->matrix[irand][jrand] = rand() % 100 + 1;
    }
}

void copy_matrix(std_matrix_t std_matrix, matrix_t *sparce_matrix)
{
    int k = 0;

    for (int i = 0; i < std_matrix.ysize; i++)
    {
        if (sparce_matrix->IA.ptr != NULL)
        {
            node_t *temp_IA = get_by_pos(&sparce_matrix->IA, i);
            temp_IA->start_column_ind = k;
            change_by_pos(temp_IA, &sparce_matrix->IA, i);
        }

        for (int j = 0; j < std_matrix.xsize; j++)
        {
            if (std_matrix.matrix[i][j] != 0)
            {
                sparce_matrix->A[k] = std_matrix.matrix[i][j];
                sparce_matrix->JA[k] = j;
                ++k;
            }
        }
    }

    sparce_matrix->curr_size = k;
}

int filling_matrix(std_matrix_t *std_matrix, matrix_t *sparce_matrix,
    const bool enter_type, const bool mv_type)
{
    if (enter_type)
    {
        int code_error = mv_type ? read_matrix(std_matrix,
            sparce_matrix->curr_size) : read_vector(std_matrix, sparce_matrix->curr_size);

        if (code_error)
        {
            return code_error;
        }
    }
    else
    {
        random_filling(std_matrix, sparce_matrix->curr_size);
    }

    if (mv_type)
    {
        transpose(std_matrix);
    }

    copy_matrix(*std_matrix, sparce_matrix);
    //sparce_matrix->xsize = std_matrix->ysize;
    //sparce_matrix->ysize = std_matrix->xsize;

    return OK;
}
