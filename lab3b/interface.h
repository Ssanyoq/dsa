#ifndef INTERFACE_H
#define INTERFACE_H

#define ERR_CODE 1
#define NOT_FOUND -2
#define ALREADY_EXISTS 2
#define OVERFLOW 3
#define SUCCESS 0

int table_init(Table **t, const char *values_path, const char *memory_path, const char *descriptor_path);

int find(const Table *t, int key);

int insert(Table *t, int key, int par_key, const char *str);

int delete(Table *t, int key);

void print_table(const Table *t);

int save_table(const Table *t, const char *filename, const char *vals_path);

void free_table(Table *t);

char *get_val(const Table *t, int key);

int *find_children(const Table *t, int par_key, int *len);
#endif