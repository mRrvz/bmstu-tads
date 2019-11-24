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

typedef struct node
{
    char *value;
    struct node *next_elem;
} hash_node_t;

typedef struct table
{
    hash_node_t *table_ptr;
    int size;
} table_t;

#endif

/*
change_tree(tree.root->right, tree.root->left);

void change_tree(node_t *node1, node_t *node2)
{
    swap(node1->value, node2->value);
    change_tree(node1->right, node2->left);
    change_tree(node1->left, node2->right);
}
*/
