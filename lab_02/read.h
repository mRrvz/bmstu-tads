#ifndef __READ_H__
#define __READ_H__

#include "structures.h"

short int read_not_primary(table_t *table, FILE *stream, short int i);

short int read_is_primary(table_t *table, FILE *stream, short int i);

short int read_appartments_address(table_t *table, FILE *stream, short int i);

short int read_appartments_params(table_t *table, FILE *stream, short int i);

short enter_area_to_del(table_t *const table, int *area);

short int read_action(short *action_type);

short int read_sort_type(short *sort_type, short *table_type);

short read_diapasone(int *min, int *max);

#endif
