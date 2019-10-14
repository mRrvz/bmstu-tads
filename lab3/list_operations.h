#ifndef __LIST_OPERATIONS_H__
#define __LIST_OPERATIONS_H__

int init_list_ptrs(int size, list_t *list);

void free_list(list_t *list);

void print_list(const list_t *const list, void (*print_node) (node_t));

node_t *get_by_pos(const list_t *list, const int pos);

void change_by_pos(node_t *node, const list_t *list, const int pos);

#endif
