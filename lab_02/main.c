#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "read.h"
#include "print.h"
#include "sorts.h"
#include "table_operations.h"
#include "timer.h"

#define MAX_SIZE 520

#define OK 0 

int main(void)
{
    setbuf(stdout, NULL);

    table_t table;
    appartments_t appartments_arr[MAX_SIZE];
    keys_t keys_arr[MAX_SIZE];
    init_table(&table, appartments_arr, keys_arr);

    short int action_type, code_error;

    while (true)
    {
        print_menu();
        code_error = read_action(&action_type);

        if (code_error)
        {
            puts("Невалидный пункт меню.");
            return code_error;
        }

        code_error = do_action(action_type, &table);

        if (code_error)
        {
            return code_error;
        }
    }

    return OK;
}
