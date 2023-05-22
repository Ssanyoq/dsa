#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    g->len++;
    g->vertices = realloc(g->vertices, g->len * sizeof(Vertex));
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
    g->vertices = realloc(g->vertices, g->len * sizeof(Vertex));
    return SUCCESS;
}

void dfs(const Graph *g, VerticesList *list_tail, int *colors, int depth, const int max_depth)
{
    printf("we're in\n");
    if (max_depth == depth)
    {
        return;
    }
    Vertex *target = list_tail->cur;
    Edge *cur = target->edges;
    for (int i = 0; cur != NULL; i++)
    {
        int index = get_index(g, cur->to);
        if (colors[index] == WHITE)
        {
            list_tail->next = malloc(sizeof(VerticesList));
            list_tail = list_tail->next;
            list_tail->next = NULL;
            list_tail->cur = cur->to;
            colors[index] = GREY;
            dfs(g, list_tail, colors, depth + 1, max_depth);
            colors[index] = BLACK;
        }
    }
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