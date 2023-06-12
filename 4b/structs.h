#ifndef STRUCTS_H
#define STRUCTS_H

#define BLACK 0
#define RED 1

typedef struct Node {
    short color;
    struct Node *left;
    struct Node *right;
    struct Node *par;
    unsigned int key;
    unsigned int val;
} Node;


#endif
