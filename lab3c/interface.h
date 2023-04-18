#ifndef INTERFACE_H
#define INTERFACE_H

#define ALREADY_EXISTS 2
#define TABLE_OVERFLOW 3
#define ERR 1
#define SUCCESS 0
#define NOT_FOUND -2

int max(int a, int b);

int get_index(const char *key, int size);

Table *table_init(int size);

int find(const Table *t, const char *key);

int insert(const Table *t, const char *key, const char *info);

int delete(const Table *t, const char *key);

void print_table(Table *t);

void free_table(const Table *t);

#endif