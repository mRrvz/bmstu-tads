#include "../headers/print.h"

#define N 100

void create_string_path(graph_t graph, char *graph_visual)
{
    char temp[N];
    sprintf(graph_visual, "%s", "digraph g{\n");

    for (int i = 0; i < graph.size; i++)
    {
        for (int j = 0; j < graph.size; j++)
        {
            if (graph.matrix[i][j] != 0)
            {
                sprintf(temp, "\t%d -> %d [label=%d]\n", i + 1, j + 1, graph.matrix[i][j]);
                strcat(graph_visual, temp);
            }
        }
    }

    strcat(graph_visual, "}");
}

static void shift_string(char *path)
{
    char buffer[N * N];
    char entry_string[N] = "[color=\"red\"]\n";

    strcpy(buffer, path + 1);

    for (int i = 0; entry_string[i] != '\0'; i++)
    {
        *(path++) = entry_string[i];
    }

    for (int i = 0; buffer[i] != '\0'; i++)
    {
        *(path++) = buffer[i];
    }

    path = '\0';
}

static void add_red_color(char *path)
{
    if (path != NULL)
    {
        while (*path++ != '\n');
        shift_string(--path);
    }
}

static void print_path(char *graph_visual, char *path)
{
    while (*path)
    {
        path++;
        int space_count = 0, i = 0;
        char *buffer = malloc(N * sizeof(char));

        while (space_count < 3 && *path != '\0')
        {
            buffer[i++] = *(path++);
            if (*(path - 1) == ' ')
            {
                space_count++;
            }
        }

        buffer[i] = '\0';
        if (buffer[0] != '>')
        {
            add_red_color(strstr(graph_visual, buffer));
        }

        space_count = 0;
        while (space_count < 2 && *path != '\0')
        {
            if (*path-- == ' ')
            {
                space_count++;
            }
        }

        path++;
        free(buffer);
    }

}

static void print_solution(char *solution_path)
{
    FILE *f = fopen("graph.dot", "w");
    fprintf(f, "%s", solution_path);
    fclose(f);

    system("dot -Tpng -O graph.dot");
    system("eog graph.dot.png");
}

void paint_graphs(const graph_t graph, char *graph_visual, char *copy_graph_visual, const int start)
{
    for (int j = 0; j < graph.size; j++)
    {
        strcpy(copy_graph_visual, graph_visual);
        print_path(copy_graph_visual, graph.paths[j]);

        if (graph.paths[j][0] != '\0')
        {
            printf("Путь: %s", graph.paths[j]);
            graph.paths[j][0] = '\0';
        }

        if (strcmp(copy_graph_visual, graph_visual))
        {
            print_solution(copy_graph_visual);
            memset(copy_graph_visual, 0, N * N);
        }
    }
}
