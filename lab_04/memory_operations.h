#ifndef __MEMORY_OPERATIONS_H__
#define __MEMORY_OPERATIONS_H__

#include "structures.h"

int new_matrix(maze_t *const maze);

void free_memory(maze_t *const matrix);

int init_stacks(stack_array_t *const array, stack_list_t *const list, const int max_stack);

int peek(stack_array_t *array, stack_list_t *list, int *i, int *j, int *direction);

int pop(stack_array_t *array, stack_list_t *list);

int push(stack_array_t *array, stack_list_t *list, const int i, const int j, const int direction);

void free_list(stack_list_t *list);

#endif
