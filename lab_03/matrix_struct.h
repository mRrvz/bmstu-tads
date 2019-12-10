#ifndef __MATRIX_STRUCT_H__
#define __MATRIX_STRUCT_H__

#include "list_struct.h"

typedef enum BOOLEAN{false = 0, true} bool;

typedef struct
{
    int xsize;
    int ysize;
    int curr_size;

    int *A;
    int *JA;
    list_t IA;
} matrix_t;

typedef struct std_matr
{
    int **matrix;
    int xsize;
    int ysize;
} std_matrix_t;

#endif
