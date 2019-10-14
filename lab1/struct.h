#ifndef __STRUCT_H__
#define __STRUCT_H__

#define MAX_MANTISSA 31
#define MAX_DEGREE 6

typedef struct number
{
    char mantissa_sign; // знак мантиссы
    char mantissa[MAX_MANTISSA * 2]; // сама мантисса
    int degree; // степень
    short int point_ind; // индекса нахождения точки
} number_t;

#endif
