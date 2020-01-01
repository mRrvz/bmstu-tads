#ifndef __PRINT_H__
#define __PRINT_H__

#include <inttypes.h>
#include <stdbool.h>
#include "struct.h"

void print_tree(tree_t tree, bool is_balanced);

void print_results(const int tree_size,
    int64_t std_tree_time, int64_t avl_tree_time, int64_t hash_table_time,
    int std_tree_compare, int balanced_tree_compare, int64_t table1_time,
    int64_t table2_time, const int table_size, int64_t file_time);

void print_hash_table(table_t table);

#endif
