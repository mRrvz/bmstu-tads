#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/print.h"

#define ASCII_APOSTROPHE 39
#define N 10000
#define MAX_HEIGHT_SIZE 10

int _height = 1;

static void create_vertex_string(const vertex_t *const vertex, char *buffer)
{
    if (vertex->right == NULL && vertex->left == NULL)
    {
        return;
    }

    char str_height[MAX_HEIGHT_SIZE];

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

static void calculate_height(vertex_t *vertex)
{
    if (vertex->right == NULL && vertex->left == NULL)
    {
        _height = 1;
    }

    if (vertex->left != NULL)
    {
        vertex->left->height = _height;
    }

    if (vertex->right != NULL)
    {
        vertex->right->height = _height;
    }

    if (vertex->right != NULL)
    {
        ++_height;
        calculate_height(vertex->right);
    }

    if (vertex->left != NULL)
    {
        ++_height;
        calculate_height(vertex->left);
    }
}

void print_tree(tree_t tree, bool is_balanced)
{
    char buffer[N] = "python3 src/painting.py '";

    if (is_balanced)
    {
        _height = 1;
        tree.root->height = 0;
        calculate_height(tree.root);
    }

    create_vertex_string(tree.root, buffer);
    buffer[strlen(buffer) - 1] = ASCII_APOSTROPHE;
    system(buffer);
}

void print_results(const int tree_size,
    int64_t std_tree_time, int64_t avl_tree_time, int64_t hash_table_time,
    int std_tree_compare, int balanced_tree_compare, int64_t table1_time,
    int64_t table2_time)
{
    printf("\n==============================================================");
    printf("\nВремя добавления в обычное ДДП: %"PRId64" тиков\n", std_tree_time);
    printf("Время добавления в АВЛ дерево: %"PRId64" тиков\n", avl_tree_time);
    printf("Время добавления в хеш-таблицу: %"PRId64" тиков\n\n", hash_table_time);
    printf("Время формирования хеш-таблицы хешированием №1: %"PRId64"\n", table1_time);
    if (table2_time != -1)
    {
        printf("Время формирования хеш-таблицы хешированием №2: %"PRId64"\n", table2_time);
    }
    printf("\nСреднее количество сравнений при поиске в ДДП: %lf\n", (double)std_tree_compare / tree_size);
    printf("Среднее количество сравнений при поиске в АВЛ-дереве: %lf\n", (double)balanced_tree_compare / tree_size);
    printf("\nРазмер памяти занимаемый обоими деревьями одинаковый: %lu байт\n",
        sizeof(vertex_t) * tree_size);
    printf("Размер памяти занимаемый хеш таблицей: %lu байт\n",
        sizeof(hash_node_t) * tree_size);
}

void print_hash_table(table_t table)
{
    fprintf(stdout, "%s", "\n======= ХЕШ-ТАБЛИЦА ======="
        "\nЯчейки без значения НЕ БУДУТ выведены на экран\n");

    fprintf(stdout, "Среднее количество сравнений для %d элементов хеш-таблицы: %lf\n",
        table.size, (double)table.total_compare / table.size);

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
