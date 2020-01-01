#ifndef __TREE_INTERFACES_H__
#define __TREE_INTERFACES_H__

#include <stdio.h>
#include <stdbool.h>

#include "struct.h"

bool check_repeats(const vertex_t *const vertex, char *string);

tree_t create_tree(FILE *f);

vertex_t *balance_tree(tree_t *const tree);

int insertion_to_tree(tree_t *const tree, char *buff);

int count_compares(FILE *f, tree_t tree);

#endif
