#ifndef __PARSING_H__
#define __PARSING_H__

#include "struct.h"

int parsing(const char *const num, number_t *const num_parsed);

int final_parsing(const number_t num1, const number_t num2, number_t *const result, short int fl);

#endif


