#include "../include/graph.h"

#define N 100

#define OK 0
#define GRAPH_ERROR 4

static int min_distance(int *distance, char *is_visited, const int size)
{
    int min = INT_MAX;
    int min_index;

    for (int i = 0; i < size; i++)
    {
        if (is_visited[i] == 0 && distance[i] <= min)
        {
            min = distance[i];
            min_index = i;
        }
    }

    return min_index;
}

static void reverse(char *string)
{
    int len = strlen(string);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = string[i];
        string[i] = string[len - i - 1];
        string[len - i - 1] = temp;
    }
}

static void save_path(graph_t graph, const int start_vertex, char *path)
{
    for (int i = 0; i < graph.size; i++)
    {
        if (i != start_vertex)
        {
            char buffer[10];
            sprintf(buffer, "%d ", i + 1);
            int j = i;

            do
            {
                strcat(graph.paths[i], buffer);
                j = path[j];
                sprintf(buffer, ">- %d ", j + 1);
            } while(j != start_vertex);

            strcat(graph.paths[i], buffer);
            reverse(graph.paths[i]);
        }
    }

}

int deijkstra(graph_t graph, int start_vertex)
{
    int *distance = malloc(graph.size * sizeof(int));
    char *is_visited = malloc(graph.size * sizeof(char));
    char *path = malloc(graph.size * sizeof(int));

    for (int i = 0; i < graph.size; i++)
    {
        *(distance + i) = INT_MAX;
        *(is_visited + i) = 0;
        *(path + i) = 0;
    }

    *(distance + start_vertex) = 0;

    for (int i = 0; i < graph.size - 1; i++)
    {
        int index_to_min = min_distance(distance, is_visited, graph.size);
        *(is_visited + index_to_min) = 1;

        for (int j = 0; j < graph.size; j++)
        {
            if (!is_visited[j] && graph.matrix[index_to_min][j] && distance[index_to_min] != INT_MAX
                && distance[index_to_min] + graph.matrix[index_to_min][j] < distance[j])
            {
                distance[j] = distance[index_to_min] + graph.matrix[index_to_min][j];
                path[j] = index_to_min;
            }
        }
    }

    save_path(graph, start_vertex, path);
    for (int i = 0; i < graph.size; i++)
    {
        if (distance[i] == INT_MAX)
        {
            fprintf(stderr, "Ошибка, граф не является связанным.\n");
            return GRAPH_ERROR;
        }
    }

    free(distance);
    free(is_visited);
    free(path);

    return OK;
}

graph_t create_graph(int size)
{
    graph_t graph;
    graph.size = size;

    graph.matrix = malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        *(graph.matrix + i) = calloc(size, sizeof(int));
    }

    graph.paths = malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++)
    {
        *(graph.paths + i) = malloc(N * sizeof(char));
    }

    return graph;
}
