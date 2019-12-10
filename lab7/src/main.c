#include "../headers/graph.h"
#include "../headers/read.h"
#include "../headers/print.h"

#define OK 0
#define FILE_ERROR 2
#define GRAPH_ERROR 4

#define N 10000

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);

    FILE *f = stdin;

    int size, code_error;

    if (argc == 1)
    {
        if ((code_error = read_graph_size(&size)))
        {
            return code_error;
        }
    }
    else
    {
        if ((f = fopen(argv[1], "r")) == NULL)
        {
            fprintf(stderr, "%s\n", "Ошибка при чтении файла.");
            return FILE_ERROR;
        }

        size = atoi(argv[2]);
    }

    graph_t graph = create_graph(size);

    if ((code_error = read_graph(graph, f)))
    {
        return code_error;
    }

    char copy_graph_visual[N];
    char graph_visual[N];
    create_string_path(graph, graph_visual);

    /*
    for (int i = 0; i < graph.size; i++)
    {
        for (int j = 0; j < graph.size; j++)
        {
            printf("%d ", graph.matrix[i][j]);
        }
        putchar('\n');
    }
    */

    for (int i = 0; i < graph.size; i++)
    {
        if (deijkstra(graph, i))
        {
            return GRAPH_ERROR;
        }

        paint_graphs(graph, graph_visual, copy_graph_visual, i);
    }

    return OK;
}
