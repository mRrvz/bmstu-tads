#ifndef __READ_H__
#define __READ_H__

#include "../headers/struct.h"

int read_word(const tree_t tree, char *string);

int read_word_table(char *string);

int read_table_size(int *size);

int read_max_compare(double *max_compare);

#endif
