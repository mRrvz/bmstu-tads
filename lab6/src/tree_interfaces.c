#include <stdlib.h>
#include <string.h>
#include "../headers/tree_interfaces.h"

#define N 100

static void create_vertex(vertex_t **vertex, char *string)
{
    *vertex = malloc(sizeof(vertex_t));
    (*vertex)->value = malloc((strlen(string) + 1) * sizeof(char));
    strncpy((*vertex)->value, string, strlen(string) + 1);

    (*vertex)->left = NULL;
    (*vertex)->right = NULL;
}

tree_t create_tree(FILE *f)
{
    tree_t tree = { 0, 0, 0 };
    char buff[N];

    fscanf(f, "%100s", buff);
    create_vertex(&tree.root, buff);

    while (fscanf(f, "%100s", buff) != EOF)
    {
        int difference;
        vertex_t *next_vertex = tree.root;
        vertex_t *curr_vertex = NULL;

        do
        {
            curr_vertex = next_vertex;
            difference = strcmp(next_vertex->value, buff);
            next_vertex = difference >= 0 ? next_vertex->right : next_vertex->left;
        } while (next_vertex != NULL);

        difference >= 0 ? create_vertex(&curr_vertex->right, buff) : create_vertex(&curr_vertex->left, buff);
    }

    return tree;
}
