#include <stdio.h>
#include <stdint.h>

#include "print.h"
#include "matrix_struct.h"

#define MAX_PRINT 30
#define MAX_MATRIX_PRINT 400

void initial_print()
{
    printf("%s\n",
        "Данная программа умножает вектор-строку на матрицу, обрабатывая их\n"
        "а) С помощью алгоритмов для обработки разреженных матриц.\n"
        "б) С помощью стандартных алгоритмов обработки матриц.\n\n"
        "В разреженном виде матрица хранится в двух массивах и одном списке: \n"
        "А - массив ненулевых элементов, JA - массив номеров столбцов для каждого элемента А "
        "\nи список JA, который содержит индекс каждого первого элемента очередной строки в массивах A и JA.\n"
        "\nВведите 0, если хотите сгенерировать матрицу и вектор-строку случайно, "
        "\nили 1, если хотите ввести матрицу и вектор-строку с клавиатуры: ");
}

void print_multiplication_results(const std_matrix_t std_matrix)
{
    if (std_matrix.xsize > MAX_PRINT)
    {
        printf("\nРезультат вычислений обычной матрицы не будет выведен на экран, так как он содержит более 30 элементов.");
        return;
    }

    puts("Результат вычислений: ");
    for (int i = 0; i < std_matrix.xsize; i++)
    {
        printf("%d ", std_matrix.matrix[0][i]);
    }
}


void print_compare_results(std_matrix_t std_matrix, matrix_t sparce_matrix,
    int64_t std_start, int64_t std_end, int64_t sparce_end, int curr_size)
{
    double one_percent = (double)(std_matrix.ysize) * std_matrix.xsize / 100;
    double how_many_in = sparce_matrix.curr_size  / one_percent;

    printf("\n\nМатрица %d x %d. Заполненность (примерная): %.1lf%% / 100%%\n", std_matrix.ysize, std_matrix.xsize, how_many_in);
    printf("\nВремя обычного перемножения:           %Ild тиков\nВремя перемножения разреженных матриц: %Ild тиков\n",
        std_end - std_start, sparce_end - std_end);
    printf("\nЗанимаемый объем памяти: \nОбычная матрица (одна):     %lu\nРазреженная матрица (одна): %lu\n",
        sizeof(int) * std_matrix.ysize * std_matrix.xsize,
        2 * sizeof(int) * curr_size + sizeof(node_t) * std_matrix.xsize);
}

void random_matrix_print(std_matrix_t matrix, std_matrix_t vector)
{
    if (matrix.xsize * matrix.ysize > MAX_MATRIX_PRINT)
    {
        printf("Матрица и вектор не будут выведены на экран, так как размер матрицы превышает %d элементов.\n", MAX_MATRIX_PRINT);
        return;
    }

    puts("\n Вектор: ");
    for (int i = 0; i < vector.xsize; i++)
    {
        printf("%3d ", vector.matrix[0][i]);
    }

    puts("\n\n Матрица:");
    for (int i = 0; i < matrix.ysize; i++)
    {
        for (int j = 0; j < matrix.xsize; j++)
        {
            printf("%3d ", matrix.matrix[i][j]);
        }

        puts("");
    }

    puts("\n");
}

void sparce_matrix_print(const matrix_t matrix)
{
    if (matrix.curr_size == 0)
    {
        printf("\n\nРазреженный вектор пуст.");
        return;
    }

    if (matrix.curr_size > MAX_PRINT)
    {
        printf("\n\nРезультат вычислений разреженной матрицы не будет выведен на экран, так как он содержит более 30 элементов.");
        return;
    }

    puts("\n\nРазреженный вектор (A):");

    for (int i = 0; i < matrix.curr_size; i++)
    {
        printf("%3d ", matrix.A[i]);
    }

    puts("\n\nМассив индексов столбцов (JA): ");

    for (int i = 0; i < matrix.curr_size; i++)
    {
        printf("%3d ", matrix.JA[i]);
    }

}
