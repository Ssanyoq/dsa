#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Node {
    int color;
    struct Node *left;
    struct Node *right;
    struct Node *par;
    unsigned int key;
    unsigned int val;
} Node;


#endif