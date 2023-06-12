#ifndef INTERFACE_H
#define INTERFACE_H

#define ALREADY_EXISTS 2
#define ERR 1
#define SUCCESS 0
#define NOT_FOUND -2

#include "structs.h"

Node *find(Node *root, const char *key);

void print_tree(const Node *root, const char *l_border, const char *r_border);

int insert(Node *new, Node **root);

int delete(Node **root, const char *key);

void free_node(Node *n);

void free_tree(Node *root);

Node *spec_find(Node *root, const char *border);

#endif