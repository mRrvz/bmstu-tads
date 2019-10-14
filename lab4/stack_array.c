#include <stdlib.h>

#include "stack_array.h"

#define OK 0
#define STACK_EMPTY 7

int array_pop(stack_array_t *array)
{
    if (!array->size)
    {
        return STACK_EMPTY;
    }

    array->size--;

    return OK;
}

int array_push(stack_array_t *array, const int i, const int j, const int direction)
{
    array_element_t new_peek;

    new_peek.i = i;
    new_peek.j = j;
    new_peek.direction = direction;

    *(array->ptr + ++array->size) = new_peek;

    return OK;
}

int array_peek(stack_array_t *array, int *i, int *j, int *direction)
{
    if (!array->ptr)
    {
        return STACK_EMPTY;
    }

    array_element_t peek;

    peek = *(array->ptr + array->size);
    *i = peek.i;
    *j = peek.j;
    *direction = peek.direction;

    return OK;
}
