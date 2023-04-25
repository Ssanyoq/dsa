#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#include "interface.h"

int insert_opt(Node *root) {
    printf("Input key: ");
    char *key = readline("");
    if (key == NULL) {
        return EOF;
    }
    printf("Input value: ");
    char *info = readline("");
    if (info == NULL) {
        free(key);
        return EOF;
    }
    Node *new = malloc(sizeof(Node));
    new->key = key;
    new->val = info;
    int out = insert(new, root);
    if (out == ALREADY_EXISTS) {
        free_node(new);
    }
    return out;
}

int delete_opt(Node *root) {
    char *key = readline("Input key: ");
    if (key == NULL) {
        return EOF;
    }
    int out = delete(root, key);
    free(key);
    return out;
}

int find_opt(Node *root) {
    char *key = readline("Input key: ");
    if (key == NULL) {
        return EOF;
    }
    Node *out = find(root, key);
    free(key);
    if (out == NULL) {
        return NOT_FOUND;
    }
    printf("Node found! key = %s, value = %s\n", out->key, out->val);
    return SUCCESS;
}

void print_tree_opt(const Node *root) {
    char *l_border = readline("Input left border: ");
    if (l_border == NULL) {
        return;
    }
    char *r_border = readline("Input right border: ");
    if (r_border == NULL) {
        free(l_border);
        return;
    }
    if (strcmp(l_border, r_border) >= 0) {
        printf("Incorrect borders\n");
        free(l_border);
        free(r_border);
        return;
    }
    print_tree(root, l_border, r_border);
}