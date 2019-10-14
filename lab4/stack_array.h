#ifndef __STACK_ARRAY_H__
#define __STACK_ARRAY_H__

#include "structures.h"

int array_pop(stack_array_t *array);

int array_push(stack_array_t *array, const int i, const int j, const int direction);

int array_peek(stack_array_t *array, int *i, int *j, int *direction);

#endif
