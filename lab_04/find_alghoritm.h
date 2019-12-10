#ifndef __FIND_ALGHORITM_H__
#define __FIND_ALGHORITM_H__

#include <stdint.h>
#include "structures.h"

int find_way(int stack_type, stack_array_t *array, stack_list_t *list, maze_t *maze,
    int *stack_size, const int max_stack);

#endif
