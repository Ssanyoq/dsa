#ifndef INTERFACE_H
#define INTERFACE_H

#define ALREADY_EXISTS 2
#define ERR 1
#define SUCCESS 0
#define NOT_FOUND -2
#define EMPTY_TREE 1

#include "structs.h"

int insert(Node **root, Node *new);

Node *find(Node *root, unsigned int key);

Node *get_uncle(Node *target);

void print_tree(const Node *root, int level);

Node *create_node();

void free_node(Node *node);

void free_tree(Node *root);

#endif