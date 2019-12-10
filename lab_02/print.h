#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdint.h>
#include "structures.h"

void print_menu();

void print_table(const table_t table, bool keys);

void print_table_keys(const table_t table);

void print_results(table_t *const table, int64_t start_table, int64_t end_table, int64_t end_keys);

void print_sorts_vs_results(short size, int64_t total_ticks, short sort_type, short table_type);

void print_by_condition(const table_t table, int i);

#endif
