#include <stdio.h>

#include "../headers/tree_interfaces.h"
#include "../headers/hash_interfaces.h"
#include "../headers/file_interfaces.h"
#include "../headers/read.h"
#include "../headers/print.h"
#include "../headers/struct.h"
#include "../headers/timer.h"

#define OK 0
#define FILE_ERROR 1
#define UPD_COEFF 0.82

#define N 100

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);

    int code_error, table_size;
    int64_t start_time, std_tree_time, avl_tree_time;
    int64_t table1_time, table2_time = -1;
    double max_compare;
    char word_to_add[N];
    FILE *f;

    if ((f = fopen(argv[1], "r+")) == NULL)
    {
        fprintf(stderr, "Ошибка при чтении файла\n");
        return FILE_ERROR;
    }

    tree_t tree = create_tree(f);
    tree_t balanced_tree = create_tree(f);
    print_tree(tree, false);

    balanced_tree.root = balance_tree(&balanced_tree);
    print_tree(balanced_tree, true);


    if ((code_error = read_word(tree, word_to_add)))
    {
        return code_error;
    }

    start_time = tick();
    insertion_to_tree(&tree, word_to_add);
    std_tree_time = tick() - start_time;
    print_tree(tree, false);

    start_time = tick();
    insertion_to_tree(&balanced_tree, word_to_add);
    balanced_tree.root = balance_tree(&balanced_tree);
    avl_tree_time = tick() - start_time;
    print_tree(balanced_tree, true);

    if ((code_error = read_table_size(&table_size)))
    {
        return code_error;
    }

    if ((code_error = read_max_compare(&max_compare)))
    {
        return code_error;
    }

    table_t table = create_hash_table(f, table_size, false, &table1_time);
    print_hash_table(table);

    if ((double)table.total_compare / table.elements > max_compare)
    {
        fprintf(stdout, "%s", "\nКоличество сравнений превышает максимально указанное.\n"
        "Произведена реструктуризация хеш-таблицы\n");
        table = create_hash_table(f, (int)(table.elements * UPD_COEFF), true, &table2_time);
        print_hash_table(table);
    }

    if ((code_error = read_word_table(word_to_add)))
    {
        return code_error;
    }

    int64_t hash_table_time = insertion_to_table(&table, word_to_add);
    print_hash_table(table);

    balanced_tree.total_compare = count_compares(f, balanced_tree);

    print_results(tree.size, std_tree_time, avl_tree_time, hash_table_time,
        tree.total_compare, balanced_tree.total_compare, table1_time, table2_time,
        count_table_size(table), insertion_to_file(f, word_to_add));
    fclose(f);

    return OK;
}
