#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

// STACK

int push(Stack *s, int new) {
    if (s->len == s->max_len) {
        return OVERFLOW;
    }
    s->elems[s->len] = new;
    s->len++;
    return SUCCESS;
}

int pop(Stack *s, int *place) {
    if (s->len == 0) {
        return EMPTY;
    }
    *place = s->elems[s->len - 1];
    s->len--;
    return SUCCESS;
}

Stack *init_stack(int max_len) {
    Stack *s = malloc(sizeof(Stack));
    s->len = 0;
    s->max_len = max_len;
    s->elems = malloc(max_len * sizeof(int));
    return s;
}

void free_stack(Stack *s) {
    free(s->elems);
    free(s);
}

// END OF STACK

Edge *delete_edge(Edge *list, Edge *target, Edge *par)
{
    if (list == target)
    {
        list = target->next;
    }
    else
    {
        par->next = target->next;
    }
    free(target);
    return list;
}

int get_index(const Graph *g, Vertex *target)
{
    for (int i = 0; i < g->len; i++)
    {
        if (target == &(g->vertices[i]))
        {
            return i;
        }
    }
    return NOT_FOUND;
}

Vertex *find(const Graph *g, const char *name)
{
    for (int i = 0; i < g->len; i++)
    {
        if (strcmp(name, g->vertices[i].name) == 0)
        {
            return &(g->vertices[i]);
        }
    }
    return NULL;
}

int add_vertex(Graph *g, const char *name) {
    Vertex *f = find(g, name);
    if (f != NULL) {
        return ALREADY_EXISTS;
    }
    if (g->max_len == g->len) {
        return OVERFLOW;
    }
    g->len++;
    g->vertices[g->len - 1].name = strdup(name);
    g->vertices[g->len - 1].edges = NULL;
    return SUCCESS;
}

int add_edge(Graph *g, const char *from, const char *to, short attitude) {
    if (attitude > 10 || attitude < -10) {
        return ERR;
    }
    Vertex *f = find(g, from);
    if (f == NULL) {
        return NOT_FOUND;
    }
    Vertex *t = find(g, to);
    if (t == NULL) {
        return NOT_FOUND;
    }
    Edge *cur = f->edges;
    while (cur != NULL) {
        if (cur->to == t) {
            return ALREADY_EXISTS;
        }
        if (cur->next == NULL) {
            break;
        }
        cur = cur->next;
    }
    Edge *new = malloc(sizeof(Edge));
    new->to = t;
    new->attitude = attitude;
    new->next = NULL;
    if (f->edges == NULL) {
        f->edges = new;
    } else {
        cur->next = new;
    }
    return SUCCESS;
}

int change_vertex(Graph *g, const char *cur_name, const char *new_name) {
    Vertex *t = find(g, cur_name);
    if (t == NULL) {
        return NOT_FOUND;
    }
    free(t->name);
    t->name = strdup(new_name);
    return SUCCESS;
}

int change_edge(Graph *g, const char *from, const char *to, short new_attitude) {
    Vertex *f = find(g, from);
    if (f == NULL) {
        return NOT_FOUND;
    }
    Edge *cur = f->edges;
    while (cur != NULL) {
        if (strcmp(cur->to->name, to) == 0) {
            cur->attitude = new_attitude;
            return SUCCESS;
        }
        cur = cur->next;
    }
    return SUCCESS;
}

int delete_edge_by_names(Graph *g, const char *from, const char *to)
{
    Vertex *from_v = find(g, from);
    if (from == NULL)
    {
        return NOT_FOUND;
    }

    Edge *cur = from_v->edges;
    Edge *par = NULL;
    while (cur != NULL)
    {
        if (strcmp(to, cur->to->name) == 0)
        {
            // found
            from_v->edges = delete_edge(from_v->edges, cur, par);
            return SUCCESS;
        }
        par = cur;
        cur = cur->next;
    }
    return NOT_FOUND;
}

int delete_vertex(Graph *g, const char *name)
{
    Vertex *target = find(g, name);
    if (target == NULL)
    {
        return NOT_FOUND;
    }
    int index = get_index(g, target);
    for (int i = 0; i < g->len; i++)
    {
        if (index == i)
        {
            continue;
        }
        Edge *par = NULL;
        Edge *cur = g->vertices[i].edges;
        while (cur != NULL)
        {
            if (cur->to == target)
            {
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
    return SUCCESS;
}


// DFS

VerticesList *dfs(const Graph *g, VerticesList *list_tail, int *colors, int depth, const int max_depth)
{
    if (max_depth == depth)
    {
        return list_tail;
    }
    Vertex *target = list_tail->cur;
    Edge *cur = target->edges;
    while (cur != NULL)
    {
        int index = get_index(g, cur->to);
        if (colors[index] == WHITE)
        {
            list_tail->next = malloc(sizeof(VerticesList));
            list_tail = list_tail->next;
            list_tail->next = NULL;
            list_tail->cur = cur->to;
            // printf("%s\n", list_tail->cur->name); // DEBUG
            colors[index] = GREY;
            list_tail = dfs(g, list_tail, colors, depth + 1, max_depth);
            colors[index] = BLACK;
        }
        cur = cur->next;
    }
    return list_tail;
}

void fill_order(const Graph *g, int i, int *visited, Stack *s) {
    // ~dfs

    visited[i] = 1;
    Edge *cur = g->vertices[i].edges;
    while (cur != NULL) {
        int index = get_index(g, cur->to);
        if (!visited[index]) {
            fill_order(g, index, visited, s);
        }
    }
    
    push(s, i);
}

void dfs_print(const Graph *g, int i, int *visited) {
    visited[i] = 1;
    printf("%s ", g->vertices[i].name);
    Edge *cur = g->vertices[i].edges;
    while (cur != NULL)
    {
        int index = get_index(g, cur->to);
        if (!visited[index]) {
            dfs_print(g, index, visited);
        }
    }
    
}

// END OF DFS


int min_dist(const int *dist, const int *shortest_set, int len) {
    int min = INT_MAX;
    int min_i = -1;
    for (int i = 0; i < len; i++) {
        if (!shortest_set[i] && dist[i] < min) {
            min = dist[i];
            min_i = i;
        }
    }
    return min_i;
}

int *shortest_path(const Graph *g, const char *src) {
    int index = get_index(g, find(g, src));
    if (index == NOT_FOUND) {
        return NULL;
    }
    int *dist = malloc(sizeof(int) * g->len); // min dist from src to ith vertex
    int *shortest_set = malloc(sizeof(int) * g->len); // was processed or not
    int *shortest_indices = malloc(sizeof(int) * g->len); // last vertex index in shortest path to ith vertex
    for (int i = 0; i < g->len; i++) {
        dist[i] = INT_MAX;
        shortest_set[i] = 0;   
        shortest_indices[i] = -1;
    }
    dist[index] = 0;

    for (int i = 0; i < g->len - 1; i++) {
        int mn_i = min_dist(dist, shortest_set, g->len);
        shortest_set[mn_i] = 1;

        for (int j = 0; j < g->len; j++) {
            Edge *cur = g->vertices[mn_i].edges;
            short are_connected = 0;
            while (cur != NULL)
            {
                if (cur->to == &(g->vertices[j]) && cur->attitude > 0) {
                    are_connected = 1;
                    break;
                }
                cur = cur->next;
            }
            if (are_connected && !shortest_set[j] && dist[mn_i] != INT_MAX && dist[mn_i] + 1 < dist[j]) {
                dist[j] = dist[mn_i] + 1;
                shortest_indices[j] = mn_i;
            }
            
        }
    }

    // for (int i = 0; i < g->len; i++) {
    //     printf("%d: %d\n", dist[i], shortest_set[i]);
    // }
    // printf("\n");

    free(dist);
    free(shortest_set);
    return shortest_indices;
}

Graph *get_transposed(const Graph *g) {
    // Transposes graph
    // a -> b = a <- b
    Graph *new = malloc(sizeof(Graph));
    new->len = g->len;
    new->max_len = g->max_len;
    new->vertices = malloc(sizeof(Vertex) * g->max_len);
    for (int i = 0; i < new->len; i++) {
        add_vertex(new, g->vertices[i].name);
    }
    for (int i = 0; i < new->len; i++) {
        Edge *cur = g->vertices[i].edges;
        while (cur != NULL)
        {
            add_edge(new, cur->to->name, g->vertices[i].name, cur->attitude);
        }
    }
    return new;
}

void scc(const Graph *g) {
    // strongly connected components
    // prints all
    Stack *s = init_stack(g->len);
    int *visited = malloc(sizeof(int) * g->len);
    for (int i = 0; i < g->len; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < g->len; i++) {
        if (!visited[i]) {
            fill_order(g, i, visited, s);
        }
    }

    Graph *trans = get_transposed(g);

    for (int i = 0; i < g->len; i++) {
        visited[i] = 0;
    }
    
    while (s->len != 0) {
        int v;
        pop(s, &v);
        if (!visited[v]) {
            dfs_print(g, v, visited);
            printf("\n");
        }
    }

    free_stack(s);
    free_graph(trans);
}

void print_graph(const Graph *g)
{
    printf("Graph: len = %d\n", g->len);
    for (int i = 0; i < g->len; i++)
    {
        printf("%i: ", i);
        if (g->vertices[i].name == NULL)
        {
            printf("NULL ");
        }
        else
        {
            printf("%s", g->vertices[i].name);
        }
        Edge *cur = g->vertices[i].edges;
        while (cur != NULL)
        {
            printf(" [%hd]->", cur->attitude);
            if (cur->to->name == NULL)
            {
                printf("NULL");
            }
            else
            {
                printf("%s", cur->to->name);
            }
            cur = cur->next;
        }
        printf("\n");
    }
    printf("\n");
}



// free
void free_edges(Edge *target)
{
    if (target == NULL)
    {
        return;
    }
    Edge *next = target->next;
    free(target);
    free_edges(next);
}

void free_graph(Graph *target)
{
    if (target == NULL)
    {
        return;
    }
    for (int i = 0; i < target->len; i++)
    {
        free_edges(target->vertices[i].edges);
        if (target->vertices[i].name != NULL)
        {
            free(target->vertices[i].name);
        }
    }
    if (target->vertices != NULL)
    {
        free(target->vertices);
    }
    free(target);
}

void free_list(VerticesList *target)
{
    if (target == NULL)
    {
        return;
    }
    VerticesList *next = target->next;
    free(target);
    free_list(next);
}