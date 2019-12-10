#ifndef __TABLE_OPERATIONS_H__
#define __TABLE_OPERATIONS_H__

#include "structures.h"

void init_table(table_t *const table, appartments_t *const appartments_arr, keys_t *const keys_arr);

void concat_address(table_t *table, char *const city, char *const street, int home_int, int appart_int, const short int i);

short int do_action(short int action_type, table_t *table);

#endif

