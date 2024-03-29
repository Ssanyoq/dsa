#ifndef MENU_H
#define MENU_H

#include "structs.h"

int insert_opt(Node **root);

int delete_opt(Node **root);

int find_opt(const Node *root);

void print_tree_opt(const Node *root);

int spec_find_opt(const Node *root);

int import_opt(Node **root);

void put_tree(Node *root, int level);

#endif