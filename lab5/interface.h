#ifndef INTERFACE_H
#define INTERFACE_H

#define ALREADY_EXISTS 2
#define ERR 1
#define SUCCESS 0
#define NOT_FOUND -2

#include "structs.h"

Vertex *find(Graph *g, const char *name);



void free_edges(Edge *target);

void free_graph(Graph *target);

void free_list(VerticesList *target);

#endif