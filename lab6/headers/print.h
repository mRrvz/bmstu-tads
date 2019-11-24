#ifndef __PRINT_H__
#define __PRINT_H__

#include <inttypes.h>
#include "struct.h"

void print_tree(tree_t tree);

void print_results(const int tree_size,
    int64_t std_tree_time, int64_t avl_tree_time, int64_t hash_table_time,
    int std_tree_compare, int balanced_tree_compare);

void print_hash_table(table_t table);

#endif
