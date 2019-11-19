#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct vertex
{
    struct vertex *left;
    struct vertex *right;
    char *value;
} vertex_t;

typedef struct tree
{
    vertex_t *root;
    int size;
    int depth;
} tree_t;

#endif
