#ifndef __DATA_OPERATIONS_H__
#define __DATA_OPERATIONS_H__

#include "struct.h"

int multp(const number_t *const num1, const number_t *const num2, number_t *const result);

void to_expon(char *const num);

int check_expon(char *const num, short int cur_len, short int len);

void rounding(number_t *const numb, short int end_ind, short int flag);

void add_degree(const number_t num1, const number_t num2, number_t *const res);

void null_rounding(number_t *const numb, short int ind);

void normalize(number_t *const num);

void add_null(char *const arr);

#endif

