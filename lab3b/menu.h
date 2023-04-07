#ifndef MENU_H
#define MENU_H

char *freadline(FILE *readfile);

int parse_file(Table *t, const char *path);

int input_option(Table *t);

int delete_option(Table *t);

int find_option(Table *t);

#endif