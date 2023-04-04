#ifndef INTERFACE_H
#define INTERFACE_H

#include "structs.h"

int add(Table *t, KeySpace *item);

KeySpace *find(int key, Table *table);

KeySpace **find_children(int key, Table *t, int *size);

int delete(Table *t, int key);

void free_table(Table *t);

#endif