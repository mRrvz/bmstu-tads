#include <stdlib.h>
#include <stdio.h>

#include "stack_list.h"

#define OK 0
#define MEMORY_ERROR 2
#define STACK_EMPTY 7

int list_pop(stack_list_t *list)
{
    list_element_t *old_peak = NULL;

    if (list->ptr == NULL)
    {
        return STACK_EMPTY;
    }

    old_peak = list->ptr;
    list->ptr = old_peak->next_elem;
    free(old_peak);

    return OK;
}

int list_push(stack_list_t *list, const int i, const int j, const int direction)
{
    list_element_t *new_peak = NULL;

    if ((new_peak = malloc(sizeof(list_element_t))) == NULL)
    {
        return MEMORY_ERROR;
    }

    new_peak->i = i;
    new_peak->j = j;
    new_peak->direction = direction;
    new_peak->next_elem = list->ptr;
    list->ptr = new_peak;

    return OK;
}

int list_peek(stack_list_t *list, int *i, int *j, int *direction)
{
    list_element_t *new_peak = NULL;

    if (list->ptr == NULL)
    {
        return STACK_EMPTY;
    }

    new_peak = list->ptr;
    *i = new_peak->i;
    *j = new_peak->j;
    *direction = new_peak->direction;

    return OK;
}
