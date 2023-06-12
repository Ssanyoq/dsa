#ifndef INTERFACE_H
#define INTERFACE_H

#define ALREADY_EXISTS 2
#define TABLE_OVERFLOW 3
#define ERR 1
#define SUCCESS 0
#define NOT_FOUND -2

#include "structs.h"

int max(int a, int b);

int get_index_by_char(const char *key, int size);

int get_index(const Table *t, const char *key);

Table *table_init(int size);

int find(const Table *t, const char *key);

int insert(const Table *t, char *key, char *info);

int delete(const Table *t, const char *key);

void print_table(const Table *t);

void free_table(Table *t);

#endif