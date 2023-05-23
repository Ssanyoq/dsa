#ifndef INTERFACE_H
#define INTERFACE_H

#define ALREADY_EXISTS 2
#define ERR 1
#define SUCCESS 0
#define NOT_FOUND -2
#define OVERFLOW 3

#define EMPTY 4

#define WHITE 0
#define GREY 1
#define BLACK 2

#include "structs.h"


// STACK

int push(Stack *s, int new);

int pop(Stack *s, int *place);

Stack *init_stack(int max_len);

void free_stack(Stack *s);

// END OF STACK

Edge *delete_edge(Edge *list, Edge *target, Edge *par);

int get_index(const Graph *g, Vertex *target);

Vertex *find(const Graph *g, const char *name);

int add_vertex(Graph *g, const char *name);

int add_edge(Graph *g, const char *from, const char *to, short attitude);

int change_vertex(Graph *g, const char *cur_name, const char *new_name);

int change_edge(Graph *g, const char *from, const char *to, short new_attitude);

int delete_edge_by_names(Graph *g, const char *from, const char *to);

int delete_vertex(Graph *g, const char *name);

// DFS

VerticesList *dfs(const Graph *g, VerticesList *list_tail, int *colors, int depth, const int max_depth);

void fill_order(const Graph *g, int i, int *visited, Stack *s);

void dfs_print(const Graph *g, int i, int *visited);

// END OF DFS

int *shortest_path(const Graph *g, const char *src);

Graph *get_transposed(const Graph *g);

void scc(const Graph *g);

void print_graph(const Graph *g);

// free
void free_edges(Edge *target);

void free_graph(Graph *target);

void free_list(VerticesList *target);

#endif