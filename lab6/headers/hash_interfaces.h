#ifndef __HASH_INTERFACES_H__
#define __HASH_INTERFACES_H__

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#include "struct.h"

int64_t insertion_to_table(table_t *const table, char *buffer);

table_t create_hash_table(FILE *f, const int size, bool is_nkey, int64_t *form_time);

int count_table_size(const table_t table);

#endif
