#ifndef __READ_H__
#define __READ_H__

#include <stdio.h>
#include "graph.h"

int read_graph_size(int *size);

int read_graph(const graph_t graph, FILE *f);

#endif
