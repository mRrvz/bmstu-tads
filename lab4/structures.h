#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

typedef enum boolean
{
    false = 0,
    true = 1
} bool;

typedef struct maze
{
    char **matrix;
    int x;
    int y;
    int i_enter;
    int j_enter;
} maze_t;

typedef struct list_element
{
    int i;
    int j;
    int direction;
    struct list_element *next_elem;
} list_element_t;

typedef struct list
{
    list_element_t *ptr;
} stack_list_t;

typedef struct array_elem
{
    int i;
    int j;
    int direction;
} array_element_t;

typedef struct array
{
    array_element_t *ptr;
    int size;
} stack_array_t;

#endif
