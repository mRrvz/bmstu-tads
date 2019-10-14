#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "struct.h"
#include "read.h"
#include "data_check.h"
#include "parsing.h"
#include "data_operations.h"

#define OK 0
#define READ_ERROR 1
#define INVALID_DATA 2
#define RANGE_ERR 3
#define RANGE_ERR_MNT 4
#define NO_SIGN 5
#define NO_DEGREE_SIGN 6

#define N 100
#define MAX_LEN 30

int main(void)
{
    setbuf(stdout, NULL);
    
    // Инициализация структур и массивов
    char *num1 = malloc(N * sizeof(char));
    char *num2 = malloc(N * sizeof(char));
    number_t num1_parsed, num2_parsed, result;
    memset(result.mantissa, '0', sizeof(result.mantissa));

    // Считывание и проверка первого (действительного) числа
    if (read_fst_num(num1))
    {
        puts("Ошибка: действительное число введено некорректно");
        return READ_ERROR;
    }


    // Приведение числа к эспоненциальному виду, если оно еще не приведено
    if (check_expon(num1, 0, strlen(num1)))
    {
        to_expon(num1);
    }
    
    // Обработка ошибок
    short int code_err = check_float(num1);
    if (code_err)
    { 
        if (code_err == NO_SIGN)
        {
            puts("Ошибка: не указан знак мантиссы");
            return NO_SIGN;
        }
        
        if (code_err == NO_DEGREE_SIGN)
        {
            puts("Ошибка: не указан знак степени");
        }

        puts("Ошибка: дейтсвительное число введено в некорректной форме");
        return INVALID_DATA;
    }
    
    // Распаршивание действительного числа в структуру
    code_err = parsing(num1, &num1_parsed);
    if (code_err == RANGE_ERR_MNT) 
    {
        puts("Ошибка: мантисса должна содержать менее 30 цифр");
        return RANGE_ERR_MNT;
    }

    if (code_err == RANGE_ERR) 
    {
        puts("Ошибка: степень должна состоять меньше, чем из 5 символов");
        return RANGE_ERR;
    }

    if (!num1_parsed.mantissa[0])
    {
        puts("Ошибка: некорректный ввод");
        return INVALID_DATA;
    }

    if (num1[1] == '.')
    {
        add_null(num1);
    }
    
    short int fl = 0;
    if (num1[1] == '0' && num1[2] == '.')
    {
        fl = 1;
        normalize(&num1_parsed);
    }

    // Считывание и проверка второго (целого) числа
    if (read_snd_num(num2))
    {
        puts("Ошибка: целое число введено некоректно");
        return READ_ERROR;
    }

    if (check_int(num2))
    {
        puts("Ошибка: целое число введено в некорректной форме");
        return INVALID_DATA;
    }

    // Приведение числа к экспоненциальному виду, если оно еще не привидено
    if (check_expon(num2, 0, strlen(num2)))
    {
        to_expon(num2);
    }
   
    // Распаршивание целого числа в структуру
    code_err = parsing(num2, &num2_parsed);
    if (code_err == RANGE_ERR_MNT) 
    {
        puts("Ошибка: целое число должно содержать менее 30 цифр");
        return RANGE_ERR_MNT;
    }

    if (code_err == RANGE_ERR) 
    {
        puts("Ошибка: степень должна содержать 5 или менее цифр");
        return RANGE_ERR;
    }

    if (!num2_parsed.mantissa[0])
    {
        puts("Ошибка: некорректный ввод");
        return INVALID_DATA;
    }
    
    free(num1);
    free(num2);
    
    // Перемножение распаршеных (в структуры) чисел
    multp(&num1_parsed, &num2_parsed, &result);

    // Приведение результата к финальному виду и обработка ошибок
    code_err = final_parsing(num1_parsed, num2_parsed, &result, fl);
    if (code_err == RANGE_ERR_MNT)
    {
        puts("Предупреждение: результат мантиссы более, чем 30 символов, поэтому он был округлен до 30 знаков.");
        rounding(&result, MAX_LEN - 2, 0);
        result.mantissa[29] = '\0';
    }

    if (code_err == RANGE_ERR)
    {
        puts("Ошибка: результат степени состоит более чем из 5 символов");
        return RANGE_ERR_MNT;
    }

    null_rounding(&result, strlen(result.mantissa) - 1);
    print_result(result);

    return OK;
}
