#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Node {
    char *key;
    char *val;
    struct Node *par;
    struct Node *left;
    struct Node *right;
    
} Node;

#endif