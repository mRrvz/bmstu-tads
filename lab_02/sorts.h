#ifndef __SORTS_H__
#define __SORTS_H__

#include "structures.h"

int comparator_keys(const void* val1, const void* val2);

int comparator_table(const void* val1, const void* val2);

void bubble_sort(const int size, void *arr, int (*comparator) (const void *val1, const void *val2), bool table, size_t size_bytes);

#endif
