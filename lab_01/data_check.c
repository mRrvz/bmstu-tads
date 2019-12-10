#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "data_check.h"

#define ARR_SZ 5
#define MAX_POINT 1
#define MAX_E 1

#define OK 0
#define INVALID_DATA 2
#define NO_SIGN 5
#define NO_DEGREE_SIGN 6

// Массив разрешенных символов
static const char allowed_symb[ARR_SZ] = { '-', '.', '+', 'e', 'E' };

// Проверка числа на допустимые символы
static int check_allowed(const char symb, int ind, int not_allowed_cnt)
{
    if (symb != allowed_symb[ind] && (symb < '0' || symb > '9'))
    {
        ++not_allowed_cnt;
    }

    if (ind < (ARR_SZ - 1))
    {
        return check_allowed(symb, ++ind, not_allowed_cnt);
    }

    if (not_allowed_cnt != ARR_SZ)
    {
        return OK;
    }

    return INVALID_DATA;
}


// Проверка, что у степени есть знак
static int sign_after_exp(const char *const num, int ind)
{
    if (toupper(num[ind]) == 'E')
    {
        if (num[++ind] != '-' && num[ind] != '+')
        {
            return NO_DEGREE_SIGN;
        }
    }

    return OK;
}

// Проверка, что знак находится в нужном месте
static int sign_and_exp_check(const char *const num, int ind)
{
    if (num[ind] == '+' || num[ind] == '-')
    {
        if (0 == ind)
        {
            return OK;
        }

        if (toupper(num[ind - 1]) == 'E')
        {
            return OK;
        }
        
        return INVALID_DATA;
    }

    return OK;
}

// Проверка, что в строке находится только лишь один символ Е
static int e_check(const char symb, short int *const e_cnt)
{
    if (toupper(symb) == 'E')
    {
        ++(*e_cnt);
    }

    if (*e_cnt > MAX_E)
    {
        return INVALID_DATA;
    }

    return OK;
}

// Проверка, что в степени нет точки
static int point_in_degree(const char *const num, const short int ind, short int *const e_cnt)
{
    if (!(*e_cnt) && num[ind] == '.')
    {
        return INVALID_DATA;
    }

    return OK;
}

static int point_cnt_check(const char *const num, short int ind, short int *const point_cnt)
{
    if (!num[ind])
    {
        return OK;
    }

    if (num[ind] == '.')
    {
        (*point_cnt)++;
    }

    if ((*point_cnt) > 1)
    {
        return INVALID_DATA;
    }

    return point_cnt_check(num, ++ind, point_cnt);
}

// Вспомогательная функция, рекурсивно проверяющая допустимые символы и знаки в строке
static int check_recurse(const char *const num, int len, short int *const e_cnt)
{
    if (check_allowed(num[len], 0, 0))
    {
        return INVALID_DATA;
    }

    if (e_check(num[len], e_cnt))
    {
        return INVALID_DATA;
    }

    if (sign_and_exp_check(num, len))
    {
        return INVALID_DATA;
    }

    if (sign_after_exp(num, len))
    {
        return NO_DEGREE_SIGN;
    }

    if (point_in_degree(num, len, e_cnt))
    {
        return INVALID_DATA;
    }

    if (0 != len)
    {
        return check_recurse(num, --len, e_cnt);
    }

    return OK;
}


int check_int(const char *const num)
{
    for (int i = 1; i < strlen(num); i++)
    {
        if (!isdigit(num[i]))
        {
            return 1;
        }
    }
    
    return 0;
}

// Функция проверяющая действительное число на корректность
int check_float(const char *const num)
{
    short int e_cnt = 0;
    short int point_cnt = 0;
    short int len = strlen(num) - 1; // взятие индекса последнего элемента в массиве num

    short int code_err = check_recurse(num, len,  &e_cnt);
    if (code_err)
    {
        if (code_err == NO_DEGREE_SIGN)
        {
            return NO_DEGREE_SIGN;
        }

        return INVALID_DATA;
    }
    
    if (check_sign(num))
    {
        return NO_SIGN;
    }

    if (toupper(num[len]) == 'E')
    {
        return INVALID_DATA;
    }

    if (num[len] == '+' || num[len] == '-')
    {
        return INVALID_DATA;
    }

    if (point_cnt_check(num, 0, &point_cnt))
    {
        return INVALID_DATA;
    }
    
    return OK;
}

// Функция, проверяющая наличие точек в целом числе
int check_point(const char *const num, short int ind)
{
    if (!num[ind])
    {
        return OK;
    }

    if (num[ind] == '.')
    {
        return INVALID_DATA;
    }
    
    return check_point(num, ++ind);
}

// Функция проверяющая наличие знака перед числом
int check_sign(const char *const num)
{
    if (num[0] != '+' && num[0] != '-')
    {
        return NO_SIGN;
    }

    return OK;
}
