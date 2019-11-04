#include <stdio.h>
#include <string.h>

#include "read.h"
#include "memory_operations.h"

#define READ_OK 1
#define MAX_SIZE 50
#define MAX_STACK 10000
#define N 50

#define OK 0
#define INVALID_INPUT 1
#define MEMORY_ERROR 2
#define INVALID_FILE 3
#define INVALID_X 4
#define INVALID_Y 5
#define INVALID_STACK_TYPE 6
#define STACK_EMPTY 7

static int read_maze(maze_t *maze, FILE *f, int *max_stack)
{
    for (int i = 0; i < maze->y; i++)
    {
        if (fgetc(f) == EOF)
        {

            return INVALID_INPUT;
        }

        for (int j = 0; j < maze->x; j++)
        {
            if ((maze->matrix[i][j] = fgetc(f)) == EOF)
            {
                return INVALID_INPUT;
            }

            if (maze->matrix[i][j] == ' ')
            {
                (*max_stack)++;
            }

            if (maze->matrix[i][j] == '0')
            {
                maze->i_enter = i;
                maze->j_enter = j;
            }
        }
    }

    return OK;
}

static int open_file(FILE **f, char *file_name)
{
    if ((*f = fopen(file_name, "r")) == NULL)
    {
        return INVALID_FILE;
    }

    return OK;
}

int read_file(maze_t *maze, FILE *f, int *max_stack)
{
    char file_name[N];
    maze->matrix = NULL;

    puts("\nДанная программа ищет выход в лабиринте с помощью стека.\n"
    "Стек реализован либо с помощью спиcка, либо с помощью массива.\n"
    "Лабиринт хранится в файле.\n");

    puts("Введите имя файла (включая путь до него): ");
    if (fscanf(stdin, "%30s", file_name) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (open_file(&f, file_name))
    {
        fprintf(stderr, "Ошибка: неудалось открыть файл.\n");
        return INVALID_FILE;
    }

    if (fscanf(f, "%d", &maze->x) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (maze->x > MAX_SIZE || maze->x < 1)
    {
        fprintf(stderr, "Ошибка: количество столбцов должно быть от 0 до 100\n");
        return INVALID_X;
    }

    if (fscanf(f, "%d", &maze->y) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (maze->y > MAX_SIZE || maze->y < 1)
    {
        fprintf(stderr, "Ошибка: количество строк должно быть от 0 до 100\n");
        return INVALID_X;
    }

    if (new_matrix(maze))
    {
        return MEMORY_ERROR;
    }

    if (read_maze(maze, f, max_stack))
    {
        fprintf(stderr, "Ошибка чтения из файла\n");
        return INVALID_INPUT;
    }

    fclose(f);

    return OK;
}

int read_stack_type(int *type)
{
    puts("\nВведите 1, если хотите использовать стек реализованный массивом,\n"
    "или 0, если хотите использовать стек реализованный списком.");

    if (scanf("%d", type) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (*type < 0 || *type > 1)
    {
        fprintf(stderr, "Ошибка: некорректный ввод.\n");
        return INVALID_STACK_TYPE;
    }

    return OK;

}

int read_action(int *action_type)
{
    puts("Введите 1, если хотите найти путь в лабиринте с помощью стека\n"
        "или введите 0, если хотите в ручном режиме работать со стеком.");

    if (scanf("%d", action_type) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (*action_type < 0 || *action_type > 1)
    {
        fprintf(stderr, "Ошибка: некорректный ввод.\n");
        return INVALID_INPUT;
    }

    return OK;
}

int read_stack_action(int *action)
{
    puts("\n1. Добавить элементы в стек.\n"
        "2. Удалить элементы из стека.\n"
        "3. Добавить случайные элементы в стек.\n"
        "4. Вывести текущее состояние стека\n"
        "5. Выйти из программы.\n"
        "Выберите пункт меню: ");

    if (scanf("%d", action) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (*action < 0 || *action > 4)
    {
        fprintf(stderr, "Ошибка: некорректный ввод.\n");
        return INVALID_INPUT;
    }

    return OK;
}

int read_add_info(int *count, int curr_stack)
{
    printf("Введите количество добавляемых элементов (не более чем %d): \n",
        MAX_STACK - curr_stack);

    if (scanf("%d", count) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (*count <= 0 || *count > MAX_STACK - curr_stack)
    {
        fprintf(stderr, "Ошибка: некорректный ввода количества добавляемых элементов.\n");
        return INVALID_INPUT;
    }

    return OK;
}

int read_delete_info(int *count, int curr_stack)
{
    if (!curr_stack)
    {
        puts("\nСтек пуст.");
        return STACK_EMPTY;
    }

    printf("Введите количество удаляемых элементов (не более чем %d): \n", curr_stack);

    if (scanf("%d", count) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (*count <= 0 || *count > curr_stack)
    {
        fprintf(stderr, "Ошибка: некорректный ввода количества удаляемых элементов.\n");
        return INVALID_INPUT;
    }

    return OK;
}

int read_struct(int *i)
{
    puts("Введите элемент стека. Введите -1, если хотите закончить ввод: ");
    if (scanf("%d", i) != READ_OK)
    {
        return INVALID_INPUT;
    }

    return OK;
}
