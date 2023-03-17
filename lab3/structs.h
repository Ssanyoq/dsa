#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    char *data;
} Item;

typedef struct {
    int key;
    int par_key;
    Item *item;
} KeySpace;

typedef struct {
    KeySpace *elems;
    int max_size;
    int cur_size;
} Table;

#endif