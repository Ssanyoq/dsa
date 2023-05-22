#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WHITE 0
#define GREY 1
#define BLACK 2

Edge *delete_edge(Edge *list, Edge *target, Edge *par) {
    if (list == target) {
        list = target->next;
    } else {
        par->next = target->next;
    }
    free(target);
    return list;
}

int get_index(const Graph *g, Vertex *target) {
    for (int i = 0; i < g->len; i++) {
        if (target == &(g->vertices[i])) {
            return i;
        }
    }
    return NOT_FOUND;
}

Vertex *find(const Graph *g, const char *name) {
    for (int i = 0; i < g->len; i++) {
        if (strcmp(name, g->vertices[i].name) == 0) {
            return &(g->vertices[i]);
        }
    }
    return NULL;
}

int delete_edge_by_names(Graph *g, const char *from, const char *to) {
    Vertex *from_v = find(g, from);
    if (from == NULL) {
        return NOT_FOUND;
    }
    
    Edge *cur = from_v->edges;
    Edge *par = NULL;
    while (cur != NULL){
        if (strcmp(to, cur->to->name) == 0) {
            // found
            from_v->edges = delete_edge(from_v->edges, cur, par);
            return SUCCESS;
        }
        par = cur;
        cur = cur->next;
    }
    return NOT_FOUND;
}

int delete_vertex(Graph *g, const char *name) {
    Vertex *target = find(g, name);
    if (target == NULL) {
        return NOT_FOUND;
    }
    int index = get_index(g, target);
    for (int i = 0; i < g->len; i++) {
        if (index == i) {
            continue;
        }
        Edge *par = NULL;
        Edge *cur = g->vertices[i].edges;
        while (cur != NULL)
        {
            if (cur->to == target) {
                g->vertices[i].edges = delete_edge(g->vertices[i].edges, cur, par);
                break;
            }
            par = cur;
            cur = cur->next;
        }
        
    }
    free(g->vertices[index].name);
    free_edges(g->vertices[index].edges);
    g->vertices[index].name = g->vertices[g->len - 1].name;
    g->vertices[index].edges = g->vertices[g->len - 1].edges;
    g->len--;
    g->vertices = realloc(g->vertices, g->len * sizeof(Vertex));
}


void dfs(const Graph *g, VerticesList *list_tail, int *colors, int depth, const int max_depth) {
    if (max_depth == depth) {
        return;
    }
    Vertex *target = list_tail->cur;
    Edge *cur = target->edges;
    for (int i = 0; cur != NULL; i++) {
        int index = get_index(g, cur->to);
        if (colors[index] == WHITE) {
            list_tail->next = malloc(sizeof(VerticesList));
            list_tail = list_tail->next;
            list_tail->next = NULL;
            colors[index] = GREY;
            dfs(g, list_tail, colors, depth + 1, max_depth);
            colors[index] = BLACK;
        }
    }
}


void free_edges(Edge *target) {
    if (target == NULL) {
        return;
    }
    Edge *next = target->next;
    free(target);
    free_edges(next);
}

void free_graph(Graph *target) {
    for (int i = 0; i < target->len; i++) {
        free_edges(target->vertices[i].edges);
        if (target->vertices[i].name != NULL) {
            free(target->vertices[i].name);
        }
    }
    free(target->vertices);
    free(target);
}

void free_list(VerticesList *target) {
    if (target == NULL) {
        return;
    }
    VerticesList *next = target->next;
    free(target);
    free_list(next);
}