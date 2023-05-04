#include "interface.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


Node *get_uncle(Node *target) {
    if (target->par == NULL) {
        return NULL; // target - root
    }
    Node *gp = target->par->par;
    if (gp == NULL) {
        return NULL; // target->par - root
    }
    if (gp->left == target->par) {
        return gp->right;
    } else {
        return gp->left;
    }
}

static int outlaw_insert(Node **root, Node *new) {
    // normal binary tree insert
    if (*root == NULL) {
        (*root) = new;
        new->par = NULL;
        new->left = NULL;
        new->right = NULL;
        return SUCCESS;
    }
    if ((*root)->key == new->key) {
        return ALREADY_EXISTS;
    } else if ((*root)->key < new->key) {
        if ((*root)->right == NULL) {
            (*root)->right = new;
            new->par = (*root);
            new->right = NULL;
            new->left = NULL;
            return SUCCESS;
        }
        root = &(*root)->right;
    } else {
        if ((*root)->left == NULL) {
            (*root)->left = new;
            new->par = (*root);
            new->right = NULL;
            new->left = NULL;
            return SUCCESS;
        }
        root = &(*root)->left;
    }
    return outlaw_insert(root, new);
}

int insert(Node **root, Node *new) {
    return outlaw_insert(root, new);
}

Node *find(Node *root, unsigned int key) {
    if (root == NULL) {
        return NULL;
    }
    if (root->key == key) {
        return root;
    } else if (root->key < key) {
        root = root->right;
    } else {
        root = root->left;
    }
    return find(root, key);
}

#define STEP 2

void print_tree(const Node *root, int level) {
    int i = level;
	if (root){
		print_tree(root->right, level + STEP);
		while (i-- > 0)
			printf("  ");

        if (root->color == RED) {
            printf("\033[0;31m"); // sets red
        } else if (root->color == BLACK) {
            // printf("\033[0;35m"); // purple
            printf("\033[0;30m"); // grey
        }
		printf("%u\n", root->key);
        printf("\033[0m"); // resets color
		print_tree(root->left, level + STEP);
	} else {
        while (i-- > 0)
			printf("  ");
        printf("\033[0;30m"); 
        printf("nil\n");
        printf("\033[0m");
    }
}


Node *create_node() {
    Node *creation = malloc(sizeof(Node));
    creation->left = NULL;
    creation->right = NULL;
    creation->par = NULL;
    creation->color = -1; // чтобы не забыть
    return creation;
}

void free_node(Node *node) {
    free(node);
}

void free_tree(Node *root) {
    if (root->left != NULL) {
        free_tree(root->left);
    }
    if (root->right != NULL) {
        free_tree(root->right);
    }
    free(root);
}

