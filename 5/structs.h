#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Vertex
{
    struct Edge *edges;
    char *name;
} Vertex;

typedef struct VerticesList {
    Vertex *cur;
    struct VerticesList *next;
} VerticesList;

typedef struct Edge {
    Vertex *to;
    short attitude;
    struct Edge *next;
} Edge;

typedef struct Graph
{
    unsigned len;
    unsigned max_len;
    Vertex *vertices;
} Graph;

typedef struct Stack {
    int max_len;
    int len; // top is [len - 1]
    int *elems;
} Stack;

#endif