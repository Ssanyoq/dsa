#ifndef INTERFACE_H
#define INTERFACE_H

#define ALREADY_EXISTS 2
#define ERR 1
#define SUCCESS 0
#define NOT_FOUND -2
#define OVERFLOW 3

#define WHITE 0
#define GREY 1
#define BLACK 2

#include "structs.h"

Edge *delete_edge(Edge *list, Edge *target, Edge *par);

int get_index(const Graph *g, Vertex *target);

Vertex *find(const Graph *g, const char *name);

int add_vertex(Graph *g, const char *name);

int add_edge(Graph *g, const char *from, const char *to, short attitude);

int change_vertex(Graph *g, const char *cur_name, const char *new_name);

int change_edge(Graph *g, const char *from, const char *to, short new_attitude);

int delete_edge_by_names(Graph *g, const char *from, const char *to);

int delete_vertex(Graph *g, const char *name);

VerticesList *dfs(const Graph *g, VerticesList *list_tail, int *colors, int depth, const int max_depth);

int *shortest_path(const Graph *g, const char *src);

void print_graph(const Graph *g);

// free
void free_edges(Edge *target);

void free_graph(Graph *target);

void free_list(VerticesList *target);

#endif