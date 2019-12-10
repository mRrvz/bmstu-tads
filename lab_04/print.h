#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdint.h>
#include "structures.h"

void print_maze(const maze_t maze);

void print_compare(const int stack_size);

void print_stack(const stack_list_t list, const stack_array_t array, FILE *f,
    list_element_t **address_array, const int size);

void print_sample_stack(const stack_list_t list, const stack_array_t array, FILE *f,
    int64_t *array_time, int64_t *list_time);

void print_results(int64_t array_time, int64_t list_time);

void print_memory_results(const int size);

#endif
