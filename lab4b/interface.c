#include "interface.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


short get_color(const Node *p) {
    if (p == NULL) {
        return BLACK;
    }
    return p->color;
}

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

Node *create_node() {
    Node *creation = malloc(sizeof(Node));
    creation->left = NULL;
    creation->right = NULL;
    creation->par = NULL;
    creation->color = -1; // чтобы не забыть
    return creation;
}

Node *rotate_left(Node *point, Node *root) {
    // returns tree's root
    Node *par = point->par;
    Node *y = point->right;
    printf("hh\n");
    point->right = y->left;
    if (y->left != NULL) {
        y->left->par = point;
    }
    printf("hsh\n");
    y->par = par;
    if (par == NULL) {
        root = y;
    } else {
        if (par->left == point) {
            par->left = y;
        } else {
            par->right = y;
        }
    }
    printf("qwe\n");
    y->left = point;
    point->par = y;
    return root;
}

Node *rotate_right(Node *point, Node *root) {
    Node *par = point->par;
    Node *y = point->left;
    point->left = y->right;
    if (y->right != NULL) {
        y->right->par = point;
    }
    y->par = par;
    if (par == NULL) {
        root = y;
    } else {
        if (par->right == point) {
            par->right = y;
        } else {
            par->left = y;
        }
    }
    y->right = point;
    point->par = y;
    return root;
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

static int insert_fixup(Node **root, Node *new) {
    if (new == *root) {
        new->color = BLACK;
        return SUCCESS; 
    }
}

int insert(Node **root, Node *new) {
    int code = outlaw_insert(root, new);
    if (code != SUCCESS) {
        return code;
    }
    
    new->color = RED;

    while (new->par->color == RED)
    {
        /* code */
    }
    
    return SUCCESS;
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

Node *find_smallest(Node *root, unsigned left_border) {
    if (root == NULL) {
        return NULL;
    }
    if (root->key <= left_border && root->right != NULL) {
        root = root->right;
    } else if (root->left != NULL) {
        if (root->left->key <= left_border && root->left->right == NULL) {
            return root;
        } else {
            root = root->left;
        }
    } else if (root->key > left_border && root->right == NULL && root->left == NULL) {
        return root;
    } else {
        return NULL;
    }
    return find_smallest(root, left_border);
}

void print_in_order(Node *root, unsigned int left_border, short is_border) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    if (root->right != NULL) {
        print_in_order(root->right, left_border, is_border);
    }

    if (root->key > left_border || !is_border) {
        if (root->color == RED) {
            printf("\033[0;31m"); // sets red
        } else if (root->color != BLACK) {
            printf("\033[0;35m"); // purple
            // printf("\033[0;30m"); // grey
        }
        printf("%u: %u\n", root->key, root->val);
        printf("\033[0m"); // resets color

        if (root->left != NULL) {
            print_in_order(root->left, left_border, is_border);
        }
    }
}

#define STEP 2

void print_tree(const Node *root, int level) {
    /*
        white -> node is black
        red -> node is red
        purple -> node has incorrect color
    */
    int i = level;
	if (root){
		print_tree(root->right, level + STEP);
		while (i-- > 0)
			printf("  ");

        if (root->color == RED) {
            printf("\033[0;31m"); // sets red
        } else if (root->color != BLACK) {
            printf("\033[0;35m"); // purple
            // printf("\033[0;30m"); // grey
        }
		printf("%u\n", root->key);
        printf("\033[0m"); // resets color
		print_tree(root->left, level + STEP);
	} else {
        while (i-- > 0)
			printf("  ");
        // printf("\033[0;30m"); 
        printf("nil\n");
        // printf("\033[0m");
    }
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

