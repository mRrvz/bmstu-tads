#ifndef __HASH_INTERFACES_H__
#define __HASH_INTERFACES_H__

#include <stdio.h>
#include <inttypes.h>

#include "struct.h"

int64_t insertion_to_table(table_t table, char *buffer);

table_t create_hash_table(FILE *f, const int size);

#endif
