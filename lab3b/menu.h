#ifndef MENU_H
#define MENU_H

char *freadline(FILE *readfile);

int parse_file(Table *t, const char *path);

int input_elem(Table *t);

int delete_elem(Table *t);

#endif