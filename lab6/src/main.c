#include <stdio.h>

#include "../headers/tree_interfaces.h"
#include "../headers/hash_interfaces.h"
#include "../headers/read.h"
#include "../headers/print.h"
#include "../headers/struct.h"

#define OK 0
#define FILE_ERROR 1

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);

    FILE *f;

    if ((f = fopen("tree.txt", "r")) == NULL)
    {
        return FILE_ERROR;
    }

    tree_t tree = create_tree(f);
    print_tree(tree);
    
    balance_tree(&tree);
    print_tree(tree);

    /*
        1. add to tree
        2. hash - table
    */


    return OK;
}
