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
    root->left->left->left = create_node();
    root->left->left->right = create_node();
    root->right->par = root;
    root->left->par = root;
    root->left->left->par = root->left;
    root->left->left->left->par = root->left->left;
    root->left->left->right->par = root->left->left;
    root->right->key = 12;
    root->key = 10;
    root->left->key = 5;
    root->left->left->key = 3;
    root->left->left->left->key = 1;
    root->left->left->right->key = 4;

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
    Node *root = NULL;
    Node *new = create_node();
    new->key = 5;
    insert(&root, new);
    print_tree(root, 0);
    
    new = create_node();
    new->key = 4;
    insert(&root, new);
    print_tree(root, 0);

    new = create_node();
    new->key = 3;
    insert(&root, new);
    print_tree(root, 0);

    new = create_node();
    new->key = 2;
    insert(&root, new);
    print_tree(root, 0);

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

void test_find_smallest() {
    Node *root = create_tree();
    Node *ans = find_smallest(root, 0);
    print_tree(root, 0);
    if (ans == NULL) {
        printf("NULL\n");
    } else {
        printf("%u\n", root->key);
    }
}

int main() {
    test_insert();
}