#include "../include/read.h"

#define READ_OK 1

#define OK 0
#define INVALID_INPUT 1

int read_graph_size(int *size)
{
    fprintf(stdout, "%s", "Введите количество городов: ");

    if (fscanf(stdin, "%d", size) != READ_OK)
    {
        return INVALID_INPUT;
    }

    return OK;
}

static int keyboard_read(const graph_t graph, FILE *f)
{
    fprintf(stdout, "%s\n", "Введите пары связанных городов (в виде цифр) и путь между ними.\n"
                            "Введите -1 -1 -1, как признак окончания ввода.");

    int i = 1, j = 1, scale = 0;

    while (i != -1 && j != -1 && scale != -1)
    {
        graph.matrix[i - 1][j - 1] = scale;
        if (graph.matrix[j - 1][i - 1] == 0)
        {
            graph.matrix[j - 1][i - 1] = scale;
        }

        if (fscanf(f, "%d %d %d", &i, &j, &scale) != 3)
        {
            return INVALID_INPUT;
        }

        /*
        if (i > graph.size || i < 1 || j > graph.size || j < 1 || scale < 1)
        {
            fprintf(stderr, "%s\n", "Некорректный ввод.");
            return INVALID_INPUT;
        }
        */
    }

    return OK;
}

static int file_read(const graph_t graph, FILE *f)
{
    for (int i = 0; i < graph.size; i++)
    {
        for (int j = 0; j < graph.size; j++)
        {
            if (fscanf(f, "%d", &graph.matrix[i][j]) != READ_OK)
            {
                fprintf(stderr, "%s", "Ошибка чтения из файла\n");
                return INVALID_INPUT;
            }
        }
    }

    return OK;
}

int read_graph(const graph_t graph, FILE *f)
{
    int code_error;

    if (f == stdin)
    {
        if ((code_error = keyboard_read(graph, f)))
        {
            return code_error;
        }
    }
    else
    {
        if ((code_error = file_read(graph, f)))
        {
            return code_error;
        }
    }

    return OK;
}
