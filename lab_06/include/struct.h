#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct vertex
{
    struct vertex *left;
    struct vertex *right;
    char *value;
    int height;
} vertex_t;

typedef struct tree
{
    vertex_t *root;
    int size;
    int height;
    int total_compare;
} tree_t;

typedef struct node
{
    char *value;
    struct node *next_elem;
} hash_node_t;

typedef struct table
{
    hash_node_t *table_ptr;
    int size;
    int total_compare;
    int elements;
} table_t;

#endif
