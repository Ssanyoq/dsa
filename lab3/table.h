#ifndef TABLE_H
#define TABLE_H
#include <stdio.h>
#include "structs.h"
// #include <stddef.h>

Table *parse_file(char *path);

char *freadline(FILE *readfile);

int find_with_inputs(Table *t);

void print_table(Table *t);

int input_elem(FILE *readfile, Table *t);

int delete_elem(Table *t);

#endif