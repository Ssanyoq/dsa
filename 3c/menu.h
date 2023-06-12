#ifndef MENU_H
#define MENU_H

#include "structs.h"

char *freadline(FILE *readfile);

Table *import_table(const char *filename);

//

int insert_opt(Table *t);

int delete_opt(Table *t);

int find_opt(const Table *t);

int import_table_opt(Table **t);

#endif