#include <stdio.h>
#include <string.h>

#include "read.h"
#include "struct.h"

#define OK 0
#define READ_ERROR 1

#define READ_OK 1

// Вывод информации о том, как вводить данные
static void how_to_ent()
{
    printf("\n%150s\n\n", "=== Умножение действительного и целого числа, не помещающихся в разрядную сетку ===");
    printf("%60s\n", "ПРАВИЛА ВВОДА");
    puts("1. Оба числа вводятся с знаком плюс (+) или минус (-)");
    puts("2. Действительное и целое число может быть введено как в экспоненциальном виде, так и в обычном");
    puts("3. Если число записано в экспоненциальном виде, то: \n3.1. Степень числа так же должна быть обязательно записана со знаком плюс (+) или минус (-)");
    puts("3.2. В записи степени должна содержаться хотя бы одна цифра");
    puts("4. Целое число может содержать не более 30 цифр");
}

static void range_print()
{
    printf("\n%57s %25s\n", "мантисса", "степень");
    printf("%32d %8d %9d %9d %2d %3d\n", 1, 10, 20, 30, 1, 5);
    printf("%71s", "±|--------|---------|---------|E±|---|\n");
}

static void fst_enter()
{
    printf("Введите действительное число: ");
}

static void snd_enter()
{
    printf("Введите ЦЕЛОЕ число: %9s", " ");
}

// Считывание первого числа
int read_fst_num(char *const num1)
{
    how_to_ent();
    range_print();
    fst_enter();

    if (scanf("%100s", num1) != READ_OK)
    {
        return READ_ERROR;
    }

    return OK;
}

// Считывание второго числа
int read_snd_num(char *const num2)
{
    snd_enter();

    if (scanf("%100s", num2) != READ_OK)
    {
        return READ_ERROR;
    }

    return OK;

}

void print_result(const number_t result)
{
    if (!strcmp("\0", result.mantissa))
    {
        printf("Результат: %23s\n", "0.0"); 
    } 
    else
    {
        if (result.degree >= 0)
        {
            printf("Результат: %20c0.%se+%d\n", result.mantissa_sign, result.mantissa, result.degree);
        }
        else
        {
            printf("Результат: %20c0.%se%d\n", result.mantissa_sign, result.mantissa, result.degree);
        }
    }
}

