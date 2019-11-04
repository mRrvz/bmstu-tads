#ifndef __READ_H__
#define __READ_H__

#include "structures.h"

int read_file(maze_t *maze, FILE *f, int *max_stack);

int read_stack_type(int *type);

int read_action(int *action_type);

int read_stack_action(int *stack_action);

int read_add_info(int *count, int curr_stack);

int read_delete_info(int *count, int curr_stack);

int read_struct(int *i);

#endif
