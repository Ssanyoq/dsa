#ifndef TABLE_H
#define TABLE_H
#include <stdio.h>
#include "structs.h"
// #include <stddef.h>

Table *parse_file(char *path);

char *freadline(FILE *readfile);

void print_table(Table *t);

#endif