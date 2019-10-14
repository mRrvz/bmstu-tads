#include <stdlib.h>
#include <stdio.h>

#include "memory_operations.h"
#include "stack_list.h"
#include "stack_array.h"

#define ARRAY_STACK 1

#define OK 0
#define MEMORY_ERROR 2
#define STACK_EMPTY 7

extern int __stack_type;

int new_matrix(maze_t *const maze)
{
    maze->matrix = malloc(maze->y * sizeof(char *));

    if (maze->matrix == NULL)
    {
        return MEMORY_ERROR;
    }

    for (int i = 0; i < maze->y; i++)
    {
        maze->matrix[i] = malloc(maze->x * sizeof(char));

        if (maze->matrix[i] == NULL)
        {
            return MEMORY_ERROR;
        }
    }

    return OK;
}

void free_memory(maze_t *const maze)
{
    if (maze->matrix == NULL)
    {
        return;
    }

    for (int i = 0; i < maze->y; i++)
    {
        if (maze->matrix[i] != NULL)
        {
            free(maze->matrix[i]);
        }
    }

    free(maze->matrix);
}

int init_stacks(stack_array_t *const array, stack_list_t *const list, const int max_stack)
{
    list->ptr = NULL;
    array->ptr = NULL;
    array->size = 0;

    if ((array->ptr = malloc(max_stack * sizeof(array_element_t))) == NULL)
    {
        return MEMORY_ERROR;
    }

    return OK;
}

int peek(stack_array_t *array, stack_list_t *list, int *i, int *j, int *direction)
{
    if (__stack_type == ARRAY_STACK)
    {
        if (array_peek(array, i, j, direction))
        {
            return STACK_EMPTY;
        }
    }
    else
    {
        if (list_peek(list, i, j, direction))
        {
            return STACK_EMPTY;
        }
    }

    return OK;
}

int pop(stack_array_t *array, stack_list_t *list)
{
    if (__stack_type == ARRAY_STACK)
    {
        if (array_pop(array))
        {
            return STACK_EMPTY;
        }
    }
    else
    {
        if (list_pop(list))
        {
            return STACK_EMPTY;
        }
    }

    return OK;
}

int push(stack_array_t *array, stack_list_t *list, const int i, const int j, const int direction)
{
    if (__stack_type == ARRAY_STACK)
    {
        if (array_push(array, i, j, direction))
        {
            return MEMORY_ERROR;
        }
    }
    else
    {
        if (list_push(list, i, j, direction))
        {
            return MEMORY_ERROR;
        }
    }

    return OK;
}

void free_list(stack_list_t *list)
{
    list_element_t *curr_element = list->ptr;

    while (curr_element != NULL)
    {
        list->ptr = curr_element->next_elem;
        free(curr_element);
        curr_element = list->ptr;
    }
}
