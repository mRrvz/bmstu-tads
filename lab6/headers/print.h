#ifndef __PRINT_H__
#define __PRINT_H__

#include <inttypes.h>
#include "struct.h"

void print_tree(tree_t tree);

void print_tree_results(const int tree_size, int64_t std_tree_time, int64_t avl_tree_time);

#endif
