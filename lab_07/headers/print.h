#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>
#include "graph.h"

void create_string_path(graph_t graph, char *graph_visual);

void paint_graphs(const graph_t graph, char *graph_visual, char *copy_graph_visual, const int start);

#endif
