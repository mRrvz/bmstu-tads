#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "read.h"
#include "multiplication.h"
#include "print.h"
#include "processing.h"
#include "matrix_struct.h"
#include "matrix_memory_manager.h"
#include "timer.h"
#include "list_struct.h"
#include "list_operations.h"

#define OK 0

int main(void)
{
    setbuf(stdout, NULL);

    matrix_t sparce_matrix, sparce_vector, sparce_result;
    std_matrix_t std_matrix, std_vector, std_result;
    list_t matrix_list, vector_list, result_list;

    int code_error;
    bool enter_type;

    initial_print();

    if ((code_error = read_type(&enter_type)))
    {
        return code_error;
    }

    if ((code_error = read_sizes(&sparce_matrix, &sparce_vector)))
    {
        return code_error;
    }

    int curr_size = sparce_matrix.curr_size;

    init_sizes(&sparce_vector, sparce_matrix.ysize);
    init_sizes(&sparce_result, sparce_matrix.xsize);

    if ((code_error = init_std_matrix(&std_matrix, sparce_matrix.xsize, sparce_matrix.ysize)))
    {
        free_memory(&std_matrix);
        return code_error;
    }

    if ((code_error = init_std_matrix(&std_vector, sparce_vector.xsize, sparce_vector.ysize)))
    {
        free_memory(&std_matrix);
        free_memory(&std_vector);
        return code_error;
    }

    if ((code_error = init_std_matrix(&std_result, sparce_matrix.xsize, sparce_vector.ysize)))
    {
        free_std_matrix(&std_matrix, &std_vector, &std_result);
        return code_error;
    }

    int *A_matrix = malloc(sizeof(int) * sparce_matrix.curr_size);
    int *JA_matrix = malloc(sizeof(int) * sparce_matrix.curr_size);
    int *JA_vector = malloc(sizeof(int) * sparce_vector.curr_size);
    int *JA_result = malloc(sizeof(int) * sparce_matrix.xsize);
    int *A_vector = malloc(sizeof(int) * sparce_vector.curr_size);
    int *A_result = malloc(sizeof(int) * sparce_result.xsize);

    if ((code_error = init_sparce_matrix(&sparce_matrix, A_matrix, JA_matrix, &matrix_list)))
    {
        free_std_matrix(&std_matrix, &std_vector, &std_result);
        return code_error;
    }

    if ((code_error = init_sparce_matrix(&sparce_vector, A_vector, JA_vector, &vector_list)))
    {
        free_std_matrix(&std_matrix, &std_vector, &std_result);
        return code_error;
    }

    if ((code_error = init_sparce_matrix(&sparce_result, A_result, JA_result, &result_list)))
    {
        free_std_matrix(&std_matrix, &std_vector, &std_result);
        return code_error;
    }

    if ((code_error = filling_matrix(&std_matrix, &sparce_matrix, enter_type, 1)))
    {
        free_all_memory(&matrix_list, &vector_list, &result_list, &std_matrix, &std_vector, &std_result);
        return code_error;
    }

    if ((code_error = filling_matrix(&std_vector, &sparce_vector, enter_type, 0)))
    {
        free_all_memory(&matrix_list, &vector_list, &result_list, &std_matrix, &std_vector, &std_result);
        return code_error;
    }

    sparce_matrix.xsize = std_matrix.xsize;
    sparce_matrix.ysize = std_matrix.ysize;

    int64_t std_start = tick();
    std_multiplication(&std_matrix, &std_vector, &std_result);
    int64_t std_end = tick();
    sparce_multiplication(&sparce_matrix, &std_vector, &sparce_result);
    int64_t sparce_end = tick();

    transpose(&std_matrix);
    random_matrix_print(std_matrix, std_vector);

    print_multiplication_results(std_result);
    sparce_matrix_print(sparce_result);
    print_compare_results(std_matrix, sparce_matrix, std_start, std_end, sparce_end, curr_size);

    //free_all_memory(&matrix_list, &vector_list, &result_list, &std_matrix, &std_vector, &std_result);

    return OK;
}
