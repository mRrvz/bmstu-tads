#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>
#include "graph.h"

void create_string_path(graph_t graph, char *graph_visual);

void print_path(char *graph_visual, char *path);

void print_solution(char *solution_path);

void paint_graphs(const graph_t graph, char *graph_visual, char *copy_graph_visual, const int start);

#endif
