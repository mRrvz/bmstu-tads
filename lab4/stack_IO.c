#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>

#include "stack_IO.h"
#include "memory_operations.h"
#include "read.h"
#include "print.h"
#include "timer.h"

#define ADD 1
#define DELETE 2
#define PRINT 3

#define OK 0
#define STACK_EMPTY 7

extern int __stack_type;

static void random_filling(stack_array_t *array, stack_list_t *list, int count,
    int64_t *array_time, int64_t *list_time)
{
    srand(time(NULL));
    int64_t start_time;

    for (int i = 0; i < count; i++)
    {
        int rand_i = rand() % 100;
        int rand_j = rand() % 100;
        int rand_dir = rand() % 4;

        __stack_type = 0;

        start_time = tick();
        push(array, list, rand_i, rand_j, rand_dir);
        *list_time += tick() - start_time;

        __stack_type = 1;

        start_time = tick();
        push(array, list, rand_i, rand_j, rand_dir);
        *array_time += tick() - start_time;
    }
}

static int add_to_stack(stack_array_t *array, stack_list_t *list)
{
    int code_error, count;
    int64_t array_time = 0, list_time = 0;

    if ((code_error = read_add_info(&count, array->size)))
    {
        return code_error;
    }

    random_filling(array, list, count, &array_time, &list_time);
    print_results(array_time, list_time);
    print_memory_results(array->size);

    return OK;
}

static void delete_elements(stack_array_t *array, stack_list_t *list, int count,
    int64_t *array_time, int64_t *list_time)
{
    int64_t start_time;

    for (int i = 0; i < count; i++)
    {
        __stack_type = 0;

        start_time = tick();
        pop(array, list);
        *list_time += tick() - start_time;

        __stack_type = 1;

        start_time = tick();
        pop(array, list);
        *array_time += tick() - start_time;
    }
}

static int delete_from_stack(stack_array_t *array, stack_list_t *list)
{
    int code_error, count;
    int64_t array_time = 0, list_time = 0;

    if ((code_error = read_delete_info(&count, array->size)))
    {
        if (code_error == STACK_EMPTY)
        {
            return OK;
        }

        return code_error;
    }

    delete_elements(array, list, count, &array_time, &list_time);
    print_results(array_time, list_time);
    print_memory_results(array->size);

    return OK;
}

static void __print_stack(stack_array_t *array, stack_list_t *list)
{
    int64_t array_time = 0, list_time = 0;

    print_sample_stack(*list, *array, stdout, &array_time, &list_time);
    print_results(array_time, list_time);
    print_memory_results(array->size);
}

int stack_samples(stack_array_t *array, stack_list_t *list)
{
    int code_error, action;

    while (true)
    {
        if ((code_error = read_stack_action(&action)))
        {
            return code_error;
        }

        switch (action)
        {
            case ADD:

                if ((code_error = add_to_stack(array, list)))
                {
                    return code_error;
                }

                break;
            case DELETE:

                if ((code_error = delete_from_stack(array, list)))
                {
                    return code_error;
                }

                break;
            case PRINT:
                __print_stack(array, list);
                break;
            default:
                free(array->ptr);
                free_list(list);
                exit(0);
        }
    }
}
