#include <stdio.h>
#include <inttypes.h>

#include "print.h"
#include "timer.h"

extern int __stack_type;

void print_maze(const maze_t maze)
{
    putchar('\n');

    for (int i = 0; i < maze.y; i++)
    {
        for (int j = 0; j < maze.x; j++)
        {
            switch (maze.matrix[i][j])
            {
                case 'X':
                    printf("\033[31m%c\033[0m", maze.matrix[i][j]);
                    break;
                case '?':
                    printf("\033[32m%c\033[0m", maze.matrix[i][j]);
                    break;
                default:
                    printf("%c", maze.matrix[i][j]);
            }
        }

        putchar('\n');
    }
}

void print_compare(const int stack_size)
{
    extern int64_t total_time;

    printf("\nВремя поиска пути: %"PRId64 " тиков \n", total_time);
    printf("Количество занимаемой памяти при реализации стека с помощью массива: %lu\n",
        stack_size * (__stack_type ? sizeof(array_element_t) : sizeof(list_element_t)));
}

void print_stack(const stack_list_t list, const stack_array_t array, FILE *f,
    list_element_t **address_array, const int size)
{
    fprintf(f, "%s\n", "Стэк:\n");

    if (__stack_type)
    {
        for (int i = array.size - 1; i >= 0; i--)
        {
            fprintf(f, "%p\n", (array.ptr + i));
        }
    }
    else
    {
        list_element_t *temp = list.ptr;

        while (temp != NULL)
        {
            fprintf(f, "%p\n", temp);
            temp = temp->next_elem;
        }

        fprintf(f, "%s", "\nСписок адресов, которые были освобождены: \n");
        for (int i = 0; i < size; i++)
        {
            fprintf(f, "%p\n", address_array[i]);
        }
    }

    fprintf(f, "%s", "\n\n");
}

static void print_struct(const int i, const int j, const int dir)
{
    printf("Элемент стека: %d\n", i);
}

void print_sample_stack(const stack_list_t list, const stack_array_t array, FILE *f,
    int64_t *array_time, int64_t *list_time)
{
    int64_t start_time;
    list_element_t *temp = list.ptr;

    if (!array.size)
    {
        fprintf(f, "%s", "\nСтек пуст\n");
        return;
    }

    fprintf(f, "Текущий размер стека: %d\n", array.size);
    //fprintf(f, "%s", "\nСтек, реализованный массивом: \n\n");

    start_time = tick();
    /*
    for (int i = array.size - 1; i >= 0; i--)
    {
        fprintf(f, "Адрес: %p\n", (array.ptr + i));
        print_struct(temp->i, temp->j, temp->direction);
        temp = temp->next_elem;
    }
    */

    *array_time += tick() - start_time;

    fprintf(f, "%s", "\nСтек, реализованный списком: \n");

    temp = list.ptr;

    start_time = tick();
    while (temp != NULL)
    {
        fprintf(f, "\nАдрес: %p\n", temp);
        print_struct(temp->i, temp->j, temp->direction);
        temp = temp->next_elem;
    }

    *list_time += tick() - start_time;
}

void print_results(int64_t array_time, int64_t list_time)
{
    printf("\nВремя обработки стека, реализованного с помощью массива: %"PRId64 "\n", array_time);
    printf("Время обработки стека, реализованного с помощью списка:  %"PRId64 "\n", list_time);
}

void print_memory_results(const int size)
{
    if (!size)
    {
        printf("Память, занимаемая массивом: %lu\nПамять, занимаемая списком:  %lu\n",
            size * sizeof(int), 2 * size * sizeof(int));
        return;
    }

    printf("Память, занимаемая массивом: %lu\nПамять, занимаемая списком:  %lu\n",
        size * sizeof(int), 2 * size * sizeof(int) + size * sizeof(list_element_t *));
}
