#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/print.h"

#define ASCII_APOSTROPHE 39
#define N 1000

static void create_vertex_string(const vertex_t *const vertex, char *buffer)
{
    if (vertex->right == NULL && vertex->left == NULL)
    {
        return;
    }

    char str_height[6];

    strcat(buffer, vertex->value);
    buffer[strlen(buffer)] = ' ';

    vertex->left == NULL ? strcat(buffer, "NULL") : strcat(buffer, vertex->left->value);
    buffer[strlen(buffer)] = ' ';

    vertex->right == NULL ? strcat(buffer, "NULL") : strcat(buffer, vertex->right->value);
    buffer[strlen(buffer)] = ' ';

    sprintf(str_height, "%d", vertex->height);
    strcat(buffer, str_height);
    buffer[strlen(buffer)] = '_';

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

    create_vertex_string(tree.root, buffer);
    buffer[strlen(buffer) - 1] = ASCII_APOSTROPHE;
    system(buffer);
}

void print_tree_results(const int tree_size, int64_t std_tree_time, int64_t avl_tree_time)
{
    printf("Время добавления в обычное ДДП: %"PRId64"\n", std_tree_time);
    printf("Время добавления в сбалансированое ДДП: %"PRId64"\n", avl_tree_time);
    printf("Размер памяти занимаемый обоими деревьями одинаковый: %lu байт\n",
        sizeof(vertex_t) * tree_size);
}
