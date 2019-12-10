#include <stdio.h>

#include "read.h"
#include "errors.h"
#include "matrix_struct.h"

#define MIN_Y 2
#define MAX_Y 10000
#define MIN_X MIN_Y
#define MAX_X MAX_Y
#define MAX_INT 2147483646

#define READ_OK 1
#define READ_SIZES_OK 2

int read_sizes(matrix_t *matrix, matrix_t *vector)
{
    long curr_size;

    puts("Введите количество строк и столбцов матрицы (от 2-х до 10 тыс.): ");
    if (scanf("%d %d", &matrix->ysize, &matrix->xsize) != READ_SIZES_OK)
    {
        return INVALID_INPUT;
    }

    if (matrix->ysize < MIN_Y || matrix->ysize > MAX_Y)
    {
        fprintf(stderr, "Некорректное количество строк.\n");
        return INVALID_Y_SIZE;
    }

    if (matrix->xsize < MIN_X || matrix->xsize > MAX_X)
    {
        fprintf(stderr, "Некорректное количество столбцов.\n");
        return INVALID_X_SIZE;
    }

    puts("Введите, сколько ненулевых элементов будет содержаться в матрице: ");
    if (scanf("%ld", &curr_size) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (curr_size > MAX_INT)
    {
        fprintf(stderr, "Заполненность не должна превышать %d элементов.\n", MAX_INT);
        return INVALID_INPUT;
    }

    matrix->curr_size = curr_size;
    long long size = (long long)matrix->xsize * matrix->ysize;

    if (matrix->curr_size < 1 || matrix->curr_size > size)
    {
        fprintf(stderr, "Некорректный ввод количества ненулевых элементов в матрице.\n");
        return INVALID_FULLNESS;
    }

    puts("Введите, сколько ненулевых элементов будет содержаться в векторе строке: ");
    if (scanf("%d", &vector->curr_size) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (vector->curr_size < 1 || vector->curr_size > matrix->ysize)
    {
        fprintf(stderr, "Некорректный ввод количества ненулевых элементов в векторе-строке.\n");
        return INVALID_FULLNESS;
    }


    return OK;
}

int read_type(bool *enter_type)
{
    short ent_type;

    if (scanf("%hi", &ent_type) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (ent_type < false || ent_type > true)
    {
        fprintf(stderr, "Вы ввели целое число, не находящееся на интервале [0, 1].\n");
        return INVALID_ENTER_TYPE;
    }

    *enter_type = ent_type;

    return OK;
}

int read_matrix(std_matrix_t *std_matrix, const int maxsize)
{
    for (int i = 0; i < std_matrix->ysize; i++)
    {
        for (int j = 0; j < std_matrix->xsize; j++)
        {
            std_matrix->matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < maxsize; i++)
    {
        int numb, i1, j1;

        printf("Введите ненулевой элемент матрицы: \n");
        if (scanf("%d", &numb) != READ_OK)
        {
            return INVALID_INPUT;
        }

        puts("Введите номер строки этого элемента (нумерация начинается с нуля): ");
        if (scanf("%d", &i1) != READ_OK)
        {
            return INVALID_INPUT;
        }

        if (i1 < 0 || i1 >= std_matrix->ysize)
        {
            fprintf(stderr, "Номер строки превышает максимальный номер строки в матрице.\n");
            return INVALID_INPUT;
        }

        puts("Введите номер столбца этого элемента (нумерация начинается с нуля): ");
        if (scanf("%d", &j1) != READ_OK)
        {
            return INVALID_INPUT;
        }

        if (j1 < 0 || j1 >= std_matrix->xsize)
        {
            fprintf(stderr, "Номер столбца превышает максимальный номер столбца в матрице.\n");
            return INVALID_INPUT;
        }

        std_matrix->matrix[i1][j1] = numb;
    }

    return OK;
}

int read_vector(std_matrix_t *std_matrix, const int maxsize)
{
    int numb, i1;

    for (int i = 0; i < maxsize; i++)
    {
        printf("Введите ненулевой элемент вектора строки: \n");
        if (scanf("%d", &numb) != READ_OK)
        {
            return INVALID_INPUT;
        }

        puts("Введите номер столбца этого элемента (нумерация начинается с нуля): ");
        if (scanf("%d", &i1) != READ_OK)
        {
            return INVALID_INPUT;
        }

        if (i1 < 0 || i1 >= std_matrix->xsize)
        {
            return INVALID_INPUT;
        }

        std_matrix->matrix[0][i1] = numb;
    }

    return OK;
}
