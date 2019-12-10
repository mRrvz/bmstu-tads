#ifndef __LIST_STRUCT_H__
#define __LIST_STRUCT_H__

typedef struct node
{
    int start_column_ind;
    struct node *next_element;
} node_t;

typedef struct list
{
    struct node *ptr;
} list_t;
// free && init funcs in list_operations.c

#endif
