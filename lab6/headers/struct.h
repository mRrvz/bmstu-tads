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
} tree_t;

#endif
