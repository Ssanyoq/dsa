#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#include "interface.h"


int insert_opt(Node **root) {
    printf("Input key: ");
    unsigned k;
    int code;
    while ((code = scanf("%u", &k)) != 1 || k < 0)
    {
        if (code == -1) {
            return EOF;
        }
        fflush(stdin);
    }
    
    printf("Input value: ");
    unsigned val;
    while ((code = scanf("%u", &val)) != 1 || val < 0)
    {       
        if (code == -1) {
            return EOF;
        }
        fflush(stdin);
    }
    
    Node *new = create_node();
    new->key = k;
    new->val = val;
    int out = insert(root, new);
    if (out == ALREADY_EXISTS) {
        free_node(new);
    }
    return out;
}

int delete_opt(Node **root) {
    printf("Input key: ");
    unsigned k;
    int code;
    while ((code = scanf("%u", &k)) != 1 || k < 0)
    {
        if (code == -1) {
            return EOF;
        }
        fflush(stdin);
    }
    int out = delete(root, k);
    return out;
}

int find_opt(Node *root) {
    printf("Input key: ");
    unsigned k;
    int code;
    while ((code = scanf("%u", &k)) != 1 || k < 0)
    {
        if (code == -1) {
            return EOF;
        }
        fflush(stdin);
    }
    Node *out = find(root, k);
    if (out == NULL) {
        return NOT_FOUND;
    }
    printf("Node found! key = %u, value = %u\n", out->key, out->val);
    return SUCCESS;
}

void print_tree_opt(Node *root) {
    printf("Input left border: ");
    unsigned k;
    int code;
    while ((code = scanf("%u", &k)) != 1 || k < 0)
    {
        if (code == -1) {
            return;
        }
        fflush(stdin);
    }
    print_in_order(root, k, 1);
}