#include <stdlib.h>
#include <string.h>

#include "../headers/hash_interfaces.h"
#include "../headers/timer.h"

#define N 100

static void create_node(table_t table, char *buffer, int key)
{
    char *buffer_ptr = malloc((strlen(buffer) + 1) * sizeof(char));
    strncpy(buffer_ptr, buffer, strlen(buffer) + 1);

    if (table.table_ptr[key].value == NULL)
    {
        table.table_ptr[key].value = buffer_ptr;
    }
    else
    {
        hash_node_t *curr_node = table.table_ptr[key].next_elem;
        hash_node_t *prev_node = &table.table_ptr[key];

        while (curr_node != NULL)
        {
            prev_node = curr_node;
            curr_node = curr_node->next_elem;
        }

        curr_node = malloc(sizeof(hash_node_t));
        curr_node->value = buffer_ptr;
        curr_node->next_elem = NULL;

        prev_node->next_elem = curr_node;
    }
}

static int create_key(char *value, const int size)
{
    int code_sum = 0;
    for (; *value; code_sum += *(value++));
    return abs(code_sum) % size;
}

static void init_table(table_t *const table, const int size)
{
    table->table_ptr = malloc(size * sizeof(hash_node_t));
    table->size = size;

    for (int i = 0; i < size; i++)
    {
        table->table_ptr[i].value = NULL;
        table->table_ptr[i].next_elem = NULL;
    }
}

table_t create_hash_table(FILE *f, const int size)
{
    char buffer[N];
    table_t table = { 0, 0 };

    init_table(&table, size);
    fseek(f, 0, SEEK_SET);

    while (fscanf(f, "%s", buffer) != EOF)
    {
        int key = create_key(buffer, size);
        create_node(table, buffer, key);
    }

    return table;
}

int64_t insertion_to_table(table_t table, char *buffer)
{
    int64_t start_time = tick();
    int key = create_key(buffer, table.size);
    int64_t end_time = tick();

    create_node(table, buffer, key);

    return end_time - start_time;
}
