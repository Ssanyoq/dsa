#ifndef MENU_H

#define MENU_H

int input_d(int *out);

int input_hd(short *out); // hd - half of d

int traverse(Graph *g);

int shortest_opt(Graph *g);

int special_opt(Graph *g);

int add_vertex_opt(Graph *g);

int add_edge_opt(Graph *g);

int delete_vertex_opt(Graph *g);

int delete_edge_opt(Graph *g);

int rename_vertex_opt(Graph *g);

int change_edge_opt(Graph *g);

#endif