#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct graph
{
    int size;
    int **matrix;
    char **paths;
} graph_t;

int deijkstra(graph_t graph, int start_vertex);

graph_t create_graph(int size);

#endif
