#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parsing.h"
#include "data_operations.h"
#include "struct.h"

#define OK 0
#define RANGE_ERR 3
#define RANGE_ERR_MNT 4

#define MAX_DEGREE_CN 8
#define MAX_DEGREE_SZ 99999

// Парсинг степени
static int parsing_degree(const char *const num, number_t *const num_parsed, short int *const ind, char *const temp_degree, short int len)
{
    short int index = *ind;

    if (num[index] == '\0')
    {
        temp_degree[len] = '\0';
        num_parsed->degree = atoi(temp_degree);
        return OK;
    }

    if (abs(len) > (MAX_DEGREE - 1))
    {
        if (isdigit(temp_degree[0]))
        {
            return OK;
        }

        return RANGE_ERR;
    }
    
    temp_degree[len] = num[index];

    ++(*ind);
    return parsing_degree(num, num_parsed, ind, temp_degree, ++len);
}

// Парсинг мантиссы
static int parsing_mantissa(const char *const num, number_t *const num_parsed, short int *const ind)
{
    short int index = *ind;
    short int len = strlen(num_parsed->mantissa);

    if (num[index] == '.')
    {
        num_parsed->point_ind = index;
        goto next_ind;
    }

    if (toupper(num[index]) == 'E')
    {
        if (num_parsed->point_ind)
        {
            num_parsed->point_ind = index - num_parsed->point_ind - 1;
        }
        ++(*ind);
        num_parsed->mantissa[len] = '\0';

        return OK;
    }

    if (len >= MAX_MANTISSA - 1)
    {
        return RANGE_ERR_MNT;
    }

    num_parsed->mantissa[len] = num[index];
    
    next_ind: ++(*ind);
    return parsing_mantissa(num, num_parsed, ind);
}

// Проверка знака у мантиссы
static void sign_check(const char *const num, number_t *const num_parsed, short int *const ind)
{
    if (!isdigit(num[*ind]))
    {
        num_parsed->mantissa_sign = num[*ind];
        ++(*ind);
    }
}

// Заполнение структуры дефолтными значениями
static void std_data(number_t *const num_parsed)
{
    memset(num_parsed->mantissa, '\0', sizeof(num_parsed->mantissa));
    num_parsed->degree = 0;
    num_parsed->mantissa_sign = '+';
    num_parsed->point_ind = 0;
}

// Главная функция, запускающая парсинг числа
int parsing(const char *const num, number_t *const num_parsed)
{
    char temp_degree[MAX_DEGREE_CN] = { '\0' };
    std_data(num_parsed);

    short int degree_ind = 0; 
    sign_check(num, num_parsed, &degree_ind);

    if (parsing_mantissa(num, num_parsed, &degree_ind))
    {
        return RANGE_ERR_MNT;
    }

    if (parsing_degree(num, num_parsed, &degree_ind, temp_degree, 0))
    {
        return RANGE_ERR;
    }

    return OK;
}

// Вспомогательная функция 
static void null_counter(const char *const fin_mantissa, int len, short int *const null_cnt, short int back_flag)
{
    if (fin_mantissa[len] == '0')
    {
        ++(*null_cnt);

        if (back_flag)
        {
            null_counter(fin_mantissa, --len, null_cnt, 1);
        } 
        else
        {
            null_counter(fin_mantissa, ++len, null_cnt, 0);
        }
    }
}

static int null_check(const number_t *num1, const int len)
{
    for (int i = 0; i < len; i++)
    {
        if (num1->mantissa[i] != '0')
        {
            return 0;
        }
    }

    return 1;
}

// Поиск индекса степени
static void find_degree(number_t *const result, int ind)
{
    if (result->mantissa[ind] == '+' || result->mantissa[ind] == '-')
    {
        result->mantissa[ind] = '\0';
        return;
    }

    find_degree(result, ++ind);
}

static int add_degree_p(const number_t num)
{
    short int len = strlen(num.mantissa) - 1;
    short int k = 0;

    while (num.mantissa[len] == '0' && len) 
    {
        ++k;
        --len;
    }

    return k;
}

// Финальный парсинг и обработка числа (уже в структуре)
int final_parsing(const number_t num1, const number_t num2, number_t *const result, short int fl)
{
    short int null_cnt_behind = 0;
    short int null_cnt_front = 0;
    short int len = strlen(result->mantissa); 

    find_degree(result, 0);

    null_counter(result->mantissa, len - 1, &null_cnt_behind, 1);
    null_counter(result->mantissa, 0, &null_cnt_front, 0);

    result->mantissa[len - null_cnt_behind] = '\0';
    strcpy(result->mantissa, (result->mantissa + null_cnt_front));
    null_cnt_behind = (fl) ? add_degree_p(num2) : null_cnt_behind;
    result-> degree = num1.degree + null_cnt_behind + (strlen(result->mantissa) - result->point_ind);

    if (null_check(result, strlen(result->mantissa)))
    {
        return OK;
    }

    if (strlen(result->mantissa) == 60)
    {
        result->mantissa[59] = '0';
    }

    if (abs(result->degree) > MAX_DEGREE_SZ)
    {
        return RANGE_ERR;
    }

    null_rounding(result, strlen(result->mantissa) - 1);
    if (strlen(result->mantissa) > (MAX_MANTISSA - 1))
    {
        return RANGE_ERR_MNT;
    }

    return OK;
}

