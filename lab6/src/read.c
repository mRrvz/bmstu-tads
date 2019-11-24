#include <stdio.h>
#include "../headers/read.h"
#include "../headers/tree_interfaces.h"

#define OK 0
#define INVALID_INPUT 2
#define ALREADY_IN 3
#define INVALID_TABLE_SIZE 4

#define MIN_TABLE_SIZE 1
#define MAX_TABLE_SIZE 1000

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

int read_word_table(char *string)
{
    fprintf(stdout, "\nВведите добавляемый элемент в таблицу: ");

    if ((fscanf(stdin, "%s", string)) != READ_OK)
    {
        return INVALID_INPUT;
    }

    return OK;
}

int read_table_size(int *size)
{
    fprintf(stdout, "\nВведите размер хеш-таблицы (от %d до %d): ",
        MIN_TABLE_SIZE, MAX_TABLE_SIZE);

    if ((fscanf(stdin, "%d", size)) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (*size < MIN_TABLE_SIZE || *size > MAX_TABLE_SIZE)
    {
        return INVALID_TABLE_SIZE;
    }

    return OK;
}
