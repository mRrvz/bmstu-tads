#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "data_operations.h"
#include "struct.h"

#define N 31
#define MAX_DEGREE_SIZE 99999
#define SIGN_DEGREE 8

#define OK 0
#define ERR_RANGE 3

// Массив хранящий информацию о текущем перемноженном разряде
static char tmp[N * 2];

// Функция превращающая char в int
static int char_to_int(const char symb)
{
    return symb - '0';
}

// Перемножение разрядов, вспомогательная функция
static void disch_multp(const char *const num1, int len1, char *const tmp, int tmp_len, const int multp_num)
{
    int disch_numb = multp_num * (num1[--len1] - '0');
    tmp[tmp_len] = (char_to_int(tmp[tmp_len]) + disch_numb % 10) + '0';
    tmp[tmp_len - 1] = (char_to_int(tmp[tmp_len - 1]) + disch_numb / 10) + '0';

    if (0 == len1)
    {
        return;
    }

    disch_multp(num1, len1, tmp, --tmp_len, multp_num);
}

// Складывание разрядов при умножении, вспомогательна функция при умножении
static void disch_sum(char *const res, const char *const tmp, int len)
{
    int disch_numb = char_to_int(tmp[len]) + char_to_int(res[len]);
    
    res[len] = (disch_numb % 10) + '0';
    res[len - 1] = (char_to_int(res[len - 1]) + disch_numb / 10) + '0';

    if (1 == len)
    {
        return;
    }

    disch_sum(res, tmp, --len);
}

// Перемножение мантисс
static void multp_mantissa(const char *const num1, const int len1, const char *const num2, int len2, char *const mantissa, int disch)
{
    int tmp_len = (N * 2 - disch);
    memset(tmp, '0', sizeof(tmp));

    disch_multp(num1, len1, tmp, tmp_len, char_to_int(num2[len2]));
    disch_sum(mantissa, tmp, (N * 2) - 1);

    if (0 == len2)
    {
        mantissa[N * N] = '\0';
        return;
    }

    multp_mantissa(num1, len1, num2, --len2, mantissa, ++disch);
}

// Определение знака у мантиссы действительного числа
static void sign_defin(const number_t *const num1, const number_t *const num2, number_t *const result)
{
    if (num1->mantissa_sign == num2->mantissa_sign)
    {
        result->mantissa_sign = '+';
    }
    else
    {
        result->mantissa_sign = '-';
    }
}

// Нахождение точки у результата
static void point_defin(const number_t *const num1, const number_t *const num2, number_t *const result)
{
    result->point_ind = num1->point_ind + num2->point_ind;
}

// Функция перемножения целого и действительного числа
int multp(const number_t *const num1, const number_t *const num2, number_t *const result)
{
    multp_mantissa(num1->mantissa, strlen(num1->mantissa), num2->mantissa, strlen(num2->mantissa) - 1, result->mantissa, 1);

    sign_defin(num1, num2, result);
    point_defin(num1, num2, result);

    return OK;
}

// Приведение числа к экспоненциальному виду
void to_expon(char *const num)
{
    short int len = strlen(num);
    num[len++] = 'e';
    num[len++] = '+';
    num[len] = '0';
}

// Функция, проверяющая, записано число в экспоненциальном виде или нет
int check_expon(char *const num, short int cur_len, short int len)
{
   if (cur_len == len) 
   {
       return 1;
   }

   if (toupper(num[cur_len]) == 'E')
   {
       return 0;
   }

   return check_expon(num, ++cur_len, len);
}

// функция округления числа
void rounding(number_t *const numb, short int end_ind, short int flag)
{
    short int int_numb = numb->mantissa[end_ind + 1] - '0';
    short int int_numb_cur = numb->mantissa[end_ind] - '0';

    if (flag)
    {
        numb->mantissa[end_ind] = ((int_numb_cur + 1) % 10) + '0';
    }

    if (numb->mantissa[end_ind + 1] >= '5')
    {
        numb->mantissa[end_ind] = ((int_numb + 1) % 10) + '0';
    }

    if (numb->mantissa[end_ind] == '0' && end_ind != 0)
    {
        rounding(numb, --end_ind, 1);
    }
}

void null_rounding(number_t *const numb, short int ind)
{
    if (numb->mantissa[ind] == '0')
    {
        numb->mantissa[ind] = '\0';

        if (ind != 0)
        {
            null_rounding(numb, --ind);
        }
    }
}

void normalize(number_t *const num)
{
    short int k = 0;
    short int len = strlen(num->mantissa);
    short int i = len - num->point_ind;
    
    while (num->mantissa[i++] == '0' && i < len)
    {
        ++k;
    }
    
    if (k == 0) return;

    num->degree -= k;

    for (int q = len - 1; q > k; q--)
    {
        num->mantissa[q - k] = num->mantissa[q];
        num->mantissa[q] = '\0';
    }
    
    num->point_ind -= k;
}

void add_null(char *const arr)
{
    short int len = strlen(arr);
    
    for (int i = len - 1; i > 0; i--)
    {
        arr[i + 1] = arr[i];
    }
}

