#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../include/tree_interfaces.h"
#include "../include/print.h"

#define N 100

int curr_size = 0;

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
    tree->total_compare += height;

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

static vertex_t *build_tree(vertex_t **list_head, int n)
{
    if (n <= 0)
    {
        return NULL;
    }

    vertex_t *left = build_tree(list_head, n / 2);
    vertex_t *root;
    create_vertex(&root, (*list_head)->value, 0);
    root->left = left;
    *list_head = (*list_head)->right;
    root->right = build_tree(list_head, n - n / 2 - 1);

    return root;
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

vertex_t *balance_tree(tree_t *const tree)
{
    create_pseudo_root(tree);
    tree_to_vine(tree->root);
    delete_pseudo_root(tree);
    return build_tree(&tree->root, tree->size);
}

int count_compares(FILE *f, tree_t tree)
{
    char buff[N];
    int compares = 0, difference;
    fseek(f, 0, SEEK_SET);

    while (fscanf(f, "%100s", buff) != EOF)
    {
        vertex_t *next_vertex = tree.root;

        do
        {
            difference = strcmp(next_vertex->value, buff);
            next_vertex = difference < 0 ? next_vertex->right : next_vertex->left;
            compares++;
        } while (difference);
    }

    return compares;
}
