#include <stdio.h>
#include "../headers/read.h"
#include "../headers/tree_interfaces.h"

#define OK 0
#define INVALID_INPUT 2
#define ALREADY_IN 3

#define READ_OK 1

int read_word(const tree_t tree, char *string)
{
    fprintf(stdout, "Введите добавляемый элемент в дерево: ");
    
    if ((fscanf(stdin, "%s", string)) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if ((check_repeats(tree.root, string)))
    {
        fprintf(stderr, "Данное слово уже содержится в дереве.\n");
        return ALREADY_IN;
    }

    return OK;
}
