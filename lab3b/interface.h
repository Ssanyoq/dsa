#ifndef INTERFACE_H
#define INTERFACE_H

#define ERR_CODE 1
#define NOT_FOUND -2
#define ALREADY_EXISTS 2
#define OVERFLOW 3
#define SUCCESS 0

int table_init(Table **t, const char *filename);

int find(const Table *t, int key);

int insert(Table *t, int key, int par_key, const char *str);

int delete(Table *t, int key);

void print_table(Table *t);

int save_table(Table *t, const char *filename);

void free_table(Table *t);

char *get_val(Table *t, int key);

#endif