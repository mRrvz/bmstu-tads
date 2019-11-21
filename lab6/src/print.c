#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/print.h"

#define N 1000

static void create_vertex_string(const vertex_t *const vertex, char *buffer)
{
    if (vertex->right == NULL && vertex->left == NULL)
    {
        return;
    }

    char str_height[6];

    strcat(buffer, vertex->value);
    strcat(buffer, " ");
    vertex->right == NULL ? strcat(buffer, "NULL") : strcat(buffer, vertex->right->value);

    strcat(buffer, " ");
    vertex->left == NULL ? strcat(buffer, "NULL") : strcat(buffer, vertex->left->value);
    strcat(buffer, " ");
    sprintf(str_height, "%d", vertex->height);
    strcat(buffer, str_height);
    strcat(buffer, "_");

    if (vertex->right != NULL)
    {
        create_vertex_string(vertex->right, buffer);
    }

    if (vertex->left != NULL)
    {
        create_vertex_string(vertex->left, buffer);
    }
}

void print_tree(tree_t tree)
{
    char buffer[N] = "python3 src/painting.py '";
    printf("%d ", buffer[strlen(buffer) - 1]);
    create_vertex_string(tree.root, buffer);
    buffer[strlen(buffer) - 1] = 39;
    system(buffer);

}
