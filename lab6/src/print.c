#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/print.h"

#define ASCII_APOSTROPHE 39
#define N 100000

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

void print_results(const int tree_size,
    int64_t std_tree_time, int64_t avl_tree_time, int64_t hash_table_time,
    int std_tree_compare, int balanced_tree_compare)
{
    printf("\nВремя добавления в обычное ДДП: %"PRId64" тиков\n", std_tree_time);
    printf("Время добавления в АВЛ дерево: %"PRId64" тиков\n", avl_tree_time);
    printf("Время добавления в хеш-таблицу: %"PRId64" тиков\n", hash_table_time);
    printf("Количество сравнений при добавлени в ДДП: %d\n", std_tree_compare);
    printf("Количество сравнений при добавлени в АВЛ дерево: %d\n", balanced_tree_compare);
    printf("Размер памяти занимаемый обоими деревьями одинаковый: %lu байт\n",
        sizeof(vertex_t) * tree_size);
    printf("Размер памяти занимаемый хеш таблицей: %lu байт\n",
        sizeof(hash_node_t) * tree_size);
}

void print_hash_table(table_t table)
{
    fprintf(stdout, "%s", "\n======= ХЕШ-ТАБЛИЦА ======="
        "\nЯчейки без значения НЕ БУДУТ выведены на экран\n");

    for (int i = 0; i < table.size; i++)
    {
        if (table.table_ptr[i].value != NULL)
        {
            printf("\nКЛЮЧ: %d | Значение: %s", i, table.table_ptr[i].value);

            if (table.table_ptr[i].next_elem != NULL)
            {
                hash_node_t *temp = table.table_ptr[i].next_elem;
                while (temp != NULL)
                {
                    printf(" | Значение: %s", temp->value);
                    temp = temp->next_elem;
                }
            }
        }
    }

    putchar('\n');
}
