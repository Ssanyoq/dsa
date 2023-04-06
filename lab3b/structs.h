#ifndef STRUCTS_H
#define STRUCTS_H

#include <stddef.h>

typedef struct Item
{
   int key;
   int par_key;
   int offset;
   int len;
} Item;

typedef struct Table {
    int max_len;
    int cur_len;
    Item *arr;
    FILE *fd;
} Table;

#endif