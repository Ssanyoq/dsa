#include "interface.h"
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>

Node *create_tree() {
    /*
    tree:
                    (10)
                    /  \
                 (5)    (12)
                /
              (3)     

    */
    Node *root = create_node();
    root->right = create_node();
    root->left = create_node();
    root->left->left = create_node();
    root->right->par = root;
    root->left->par = root;
    root->left->left->par = root->left;
    root->right->key = 12;
    root->key = 10;
    root->left->key = 5;
    root->left->left->key = 3;

    root->color = BLACK;
    root->left->color = RED;
    root->left->left->color = BLACK;
    // root->right->color = BLACK;
    return root;
}

void test_get_uncle() {
    /*
    correct answer: 12;
    incorrect answer: any other
    */
    Node *root = create_tree();
    printf("%u", get_uncle(root->left->left)->key);
}

void test_insert() {
    Node *root = create_tree();
    Node *new = create_node();
    
    new->key = 3;
    
    int code = insert(&root, new);
    printf("Code is %d\n", code);
    if (code == SUCCESS) {
        printf("Parent key is %d\n", new->par->key);
    }
}

void test_find() {
    Node *root = create_tree();
    unsigned int key = 123;
    Node *out = find(root, key);
    if (out == NULL) {
        printf("Not found\n");
    } else {
        printf("Key is %u\n", out->key);
    }
}

int main() {
    Node *root = create_tree();
    print_tree(root, 0);
}