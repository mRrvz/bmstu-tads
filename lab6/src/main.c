#include <stdio.h>

#include "../headers/tree_interfaces.h"
#include "../headers/hash_interfaces.h"
#include "../headers/read.h"
#include "../headers/print.h"
#include "../headers/struct.h"
#include "../headers/timer.h"

#define OK 0
#define FILE_ERROR 1

#define N 100

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);

    int code_error;
    FILE *f;

    if ((f = fopen("tree.txt", "r")) == NULL)
    {
        return FILE_ERROR;
    }

    tree_t tree = create_tree(f);
    tree_t balanced_tree = create_tree(f);
    print_tree(tree);

    balance_tree(&balanced_tree);
    print_tree(balanced_tree);

    char word_to_add[N];

    if ((code_error = read_word(tree, word_to_add)))
    {
        return code_error;
    }

    int64_t start_time = tick();
    insertion_to_tree(&tree, word_to_add);
    int64_t std_tree_time = tick() - start_time;
    print_tree(tree);

    start_time = tick();
    insertion_to_tree(&balanced_tree, word_to_add);
    int64_t avl_tree_time = tick() - start_time;
    print_tree(balanced_tree);

    print_tree_results(tree.size, std_tree_time, avl_tree_time);

    /*
        1. hash - table
    */


    return OK;
}
