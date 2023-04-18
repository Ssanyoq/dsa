#ifndef STRUCTS_H
#define STRUCTS_H
typedef struct KeySpace
{
    int busy; // 0 - del/empty, 1 - busy
    char *key;
    char *info;
} KeySpace;

typedef struct Table
{
    int max_size;
    int cur_size;
    KeySpace *arr;
} Table;

#endif