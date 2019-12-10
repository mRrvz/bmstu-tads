#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "print.h"
#include "find_alghoritm.h"
#include "read.h"
#include "structures.h"
#include "memory_operations.h"
#include "stack_IO.h"

#define MAX_STACK 10005

#define OK 0

int main(void)
{
    setbuf(stdout, NULL);

    maze_t maze;
    stack_array_t stack_array;
    stack_list_t stack_list;

    int code_error, stack_type, action_type;
    int stack_size = 0, max_stack = 0;
    FILE *f = NULL;

    if ((code_error = read_action(&action_type)))
    {
        return code_error;
    }

    if (!action_type)
    {
        if ((code_error = init_stacks(&stack_array, &stack_list, MAX_STACK)))
        {
            return code_error;
        }

        if ((code_error = stack_samples(&stack_array, &stack_list)))
        {
            free(stack_array.ptr);
            free_list(&stack_list);
            return code_error;
        }
    }

    if ((code_error = read_file(&maze, f, &max_stack)))
    {
        if (f != NULL)
        {
            fclose(f);
        }

        free_memory(&maze);
        return code_error;
    }

    if ((code_error = init_stacks(&stack_array, &stack_list, max_stack)))
    {
        free(stack_array.ptr);
        free_memory(&maze);
        return code_error;
    }

    if ((code_error = read_stack_type(&stack_type)))
    {
        free(stack_array.ptr);
        free_memory(&maze);
        return code_error;
    }

    if ((code_error = find_way(stack_type, &stack_array, &stack_list, &maze, &stack_size, max_stack)))
    {
        free(stack_array.ptr);
        free_list(&stack_list);
        free_memory(&maze);
        return code_error;
    }

    print_maze(maze);
    print_compare(stack_size);

    free_memory(&maze);
    free_list(&stack_list);
    free(stack_array.ptr);

    return OK;
}
