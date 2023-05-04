#ifndef INTERFACE_H
#define INTERFACE_H

#define ALREADY_EXISTS 2
#define ERR 1
#define SUCCESS 0
#define NOT_FOUND -2
#define EMPTY_TREE 1

#include "structs.h"

Node *create_node();

Node *get_uncle(Node *target);

Node *rotate_left(Node *point, Node *root);

Node *rotate_right(Node *point, Node *root);

int insert(Node **root, Node *new);

Node *find(Node *root, unsigned int key);

Node *find_smallest(Node *root, unsigned left_border);

void print_tree(const Node *root, int level);

void print_in_order(Node *root, unsigned int left_border, short is_border);

void free_node(Node *node);

void free_tree(Node *root);

#endif