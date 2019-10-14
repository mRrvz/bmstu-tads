#ifndef __STACK_LIST_H__
#define __STACK_LIST_H__

#include "structures.h"

int list_pop(stack_list_t *list);

int list_push(stack_list_t *list, const int i, const int j, const int direction);

int list_peek(stack_list_t *list, int *i, int *j, int *direction);

#endif
