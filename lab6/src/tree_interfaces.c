#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../headers/tree_interfaces.h"

#define N 100

bool check_repeats(const vertex_t *const vertex, char *string)
{
    if (vertex->right == NULL && vertex->left == NULL)
    {
        return false;
    }

    if (!strcmp(vertex->value, string))
    {
        return true;
    }

    if (vertex->right != NULL)
    {
        return check_repeats(vertex->right, string);
    }

    if (vertex->left != NULL)
    {
        return check_repeats(vertex->left, string);
    }
}


static void create_vertex(vertex_t **vertex, char *string, int height)
{
    *vertex = malloc(sizeof(vertex_t));
    (*vertex)->value = malloc((strlen(string) + 1) * sizeof(char));
    strncpy((*vertex)->value, string, strlen(string) + 1);

    (*vertex)->left = NULL;
    (*vertex)->right = NULL;
    (*vertex)->height = height;
}

int insertion_to_tree(tree_t *const tree, char *buff)
{
    int difference, height = 0;
    vertex_t *next_vertex = tree->root;
    vertex_t *curr_vertex = NULL;

    do
    {
        curr_vertex = next_vertex;
        difference = strcmp(next_vertex->value, buff);
        next_vertex = difference < 0 ? next_vertex->right : next_vertex->left;
        height++;
    } while (next_vertex != NULL);

    difference < 0 ? create_vertex(&curr_vertex->right, buff, height) : create_vertex(&curr_vertex->left, buff, height);

    tree->height = height > tree->height ? height : tree->height;
    tree->size++;

    return height;
}

tree_t create_tree(FILE *f)
{
    tree_t tree = { NULL, 1, 0 };
    char buff[N];

    fseek(f, 0, SEEK_SET);
    fscanf(f, "%100s", buff);
    create_vertex(&tree.root, buff, 0);

    while (fscanf(f, "%100s", buff) != EOF)
    {
        insertion_to_tree(&tree, buff);
    }

    return tree;
}

static void create_pseudo_root(tree_t *const tree)
{
    vertex_t *pseudo_root = malloc(sizeof(vertex_t));

    pseudo_root->left = NULL;
    pseudo_root->right = tree->root;
    tree->root = pseudo_root;
}

static void delete_pseudo_root(tree_t *const tree)
{
    vertex_t *temp = tree->root;
    tree->root = tree->root->right;
    free(temp);
}

static void compress(vertex_t *const root, int count)
{
    vertex_t *scanner = root;

    for (int i = 0; i < count; i++)
    {
        vertex_t *child = scanner->right;
        scanner->right = child->right;
        scanner = scanner->right;
        child->right = scanner->left;
        scanner->left = child;
    }
}

static void vine_to_tree(vertex_t *const root, int size)
{
    int leaves = size + 1 - pow(2.0, log2(size + 1));
    compress(root, leaves);
    size -= leaves;

    while (size > 1)
    {
        compress(root, size / 2);
        size /= 2;
    }
}

static void tree_to_vine(vertex_t *const root)
{
    vertex_t *tail = root;
    vertex_t *rest = tail->right;

    while (rest != NULL)
    {
        if (rest->left == NULL)
        {
            tail = rest;
            rest = rest->right;
        }
        else
        {
            vertex_t *temp = rest->left;
            rest->left = temp->right;
            temp->right = rest;
            rest = temp;
            tail->right = temp;
        }
    }
}

void balance_tree(tree_t *const tree)
{
    create_pseudo_root(tree);

    tree_to_vine(tree->root);
    vine_to_tree(tree->root, tree->size);

    delete_pseudo_root(tree);
}
