#include <stdlib.h>
#include <stdio.h>

#include "list_struct.h"

#define OK 0
#define MEMORY_ERROR 1

int init_list_ptrs(int size, list_t *list)
{
    list->ptr = NULL;

    for (int i = 0; i < size; i++)
    {
        node_t *curr_element = malloc(sizeof(node_t));

        if (curr_element == NULL)
        {
            puts("Memory error, try again.");
            return MEMORY_ERROR;
        }

        curr_element->next_element = list->ptr;
        curr_element->start_column_ind = -1;
        list->ptr = curr_element;
    }

    return OK;
}

void free_list(list_t *list)
{
    node_t *curr, *temp;
    curr = list->ptr;

    while (curr->next_element != NULL)
    {
        temp = curr->next_element;
        free(curr);
        curr = temp;
    }

    free(temp);
}

void print_list(const list_t *const list, void (*print_node) (node_t))
{
    node_t *node = list->ptr;

    if (node == NULL)
    {
        puts("List is clean");
        return;
    }

    while (node->next_element != NULL)
    {
        (*print_node)(*node);
        node = node->next_element;
    }

    (*print_node)(*node);
}

node_t *get_by_pos(const list_t *list, const int pos)
{
    node_t *temp_node = list->ptr;

    for (int i = 0; i < pos; i++)
    {
        if (temp_node->next_element == NULL)
        {
            //fprintf(stderr, "Ошибка индекса\n");
            return temp_node;
        }

        temp_node = temp_node->next_element;
    }

    return temp_node;
}

void change_by_pos(node_t *node, const list_t *list, const int pos)
{
    node_t *temp_node = get_by_pos(list, pos);
    *temp_node = *node;
}
