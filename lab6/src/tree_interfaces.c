#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../headers/tree_interfaces.h"
#include "../headers/print.h"

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

static vertex_t *build_tree(vertex_t **nodes, int start, int end)
{
    printf("%d %d\n", start, end);
    if (start > end)
    {
        return NULL;
    }

    int mid = (start + end) / 2;
    vertex_t *root = nodes[mid];
    root->left = build_tree(nodes, start, mid - 1);
    root->right = build_tree(nodes, mid + 1, end);

    return root;
}

static void init_nodes_array(vertex_t *root, vertex_t **nodes)
{
    if (root == NULL)
    {
        return;
    }

    init_nodes_array(root->left, nodes);
    nodes[curr_size++] = root->left;
    printf("%p size\n", nodes[curr_size - 1]);
    init_nodes_array(root->right, nodes);
}

vertex_t *balance_tree(tree_t *const tree)
{
    vertex_t *nodes[100];
    init_nodes_array(tree->root, nodes);
    for (int i = 0; i < tree->size; i++)
    {
        printf("%p p", nodes[i]);
    }
    return build_tree(nodes, 0, tree->size - 1);
}
