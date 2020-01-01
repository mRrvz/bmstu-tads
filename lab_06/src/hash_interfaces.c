#include <stdlib.h>
#include <string.h>

#include "../include/hash_interfaces.h"
#include "../include/timer.h"

#define N 100

int64_t insert_time;

static int create_node(table_t table, char *buffer, int key)
{
    int avg_compare = 1;
    char *buffer_ptr = malloc((strlen(buffer) + 1) * sizeof(char));
    strncpy(buffer_ptr, buffer, strlen(buffer) + 1);

    int64_t start_time = tick();

    if (table.table_ptr[key].value == NULL)
    {
        table.table_ptr[key].value = buffer_ptr;
    }
    else
    {
        hash_node_t *curr_node = table.table_ptr[key].next_elem;
        hash_node_t *prev_node = &table.table_ptr[key];

        avg_compare++;
        while (curr_node != NULL)
        {
            avg_compare++;
            prev_node = curr_node;
            curr_node = curr_node->next_elem;
        }

        curr_node = malloc(sizeof(hash_node_t));
        curr_node->value = buffer_ptr;
        curr_node->next_elem = NULL;

        prev_node->next_elem = curr_node;
    }

    insert_time = tick() - start_time;

    return avg_compare;
}

static int create_key(char *value, const int size)
{
    int code_sum = 0;
    for (; *value; code_sum += *(value++));
    return code_sum % size;
}

static int create_new_key(char *value, const int size)
{
    unsigned long pow = 1, code_pow = 0;
    int pow_multiplier = 26;

    do
    {
        code_pow += *value * pow;
        pow *= pow_multiplier;
    } while (*(value++));

    return code_pow % size;
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

table_t create_hash_table(FILE *f, const int size, bool is_nkey, int64_t *form_time)
{
    char buffer[N];
    int64_t start_time, end_time;
    table_t table = { 0, 0, 0, 0 };

    init_table(&table, size);
    fseek(f, 0, SEEK_SET);
    *form_time = 0;

    while (fscanf(f, "%s", buffer) != EOF)
    {
        start_time = tick();
        int key = is_nkey ? create_new_key(buffer, size) : create_key(buffer, size);
        table.total_compare += create_node(table, buffer, key);
        end_time = tick();
        table.elements++;
        *form_time += end_time - start_time;
    }

    return table;
}

int64_t insertion_to_table(table_t *const table, char *buffer)
{
    int key = create_key(buffer, table->size);

    insert_time = 0;
    table->total_compare += create_node(*table, buffer, key);
    table->size++;

    return insert_time;
}

int count_table_size(const table_t table)
{
    int table_size = table.elements + table.size + 1;

    for (int i = 0; i < table.size; i++)
    {
        if (table.table_ptr[i].value != NULL)
        {
            table_size--;
        }
    }

    return table_size;
}
