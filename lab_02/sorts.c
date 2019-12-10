#include <stdio.h>

#include "sorts.h"
#include "structures.h"

static void swap(bool table, void *val1, void *val2)
{
    if (table)
    {
        appartments_t temp = *(appartments_t*)val1;
        *(appartments_t*)val1 = *(appartments_t*)(val2);
        *(appartments_t*)val2 = temp;
    }
    else
    {
        keys_t temp = *(keys_t*)val1;
        *(keys_t*)val1 = *(keys_t*)(val2);
        *(keys_t*)val2 = temp;
    }
}

int comparator_keys(const void *val1, const void *val2)
{
    return ((keys_t*)(val1))->area - ((keys_t*)(val2))->area;
}

int comparator_table(const void *val1, const void *val2)
{
    return ((appartments_t*)(val1))->area - ((appartments_t*)(val2))->area;
}

void bubble_sort(const int size, void *arr, int (*comparator) 
    (const void *val1, const void *val2), bool table, size_t size_bytes)
{
    for (int i = 0; i < size * size_bytes - size_bytes; i += size_bytes)
    {
        for (int j = 0; j < size * size_bytes- i - size_bytes; j += size_bytes)
        {
            if ((*comparator)((arr + j), (arr + j + size_bytes)) > 0)
            {
                swap(table, (arr + j), (arr + j + size_bytes));
            } 
        }

    }
}

