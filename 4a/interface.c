#include "interface.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


Node *find(Node *root, const char *key) {
    if (root == NULL) {
        return NULL;
    }
    int cmp = strcmp(root->key, key);
    if (cmp == 0) {
        return root;
    } else if (cmp < 0) {
        root = root->right;
    } else {
        root = root->left;
    }
    return find(root, key);
}

void print_tree(const Node *root, const char *l_border, const char *r_border) {
    // reversed order, [l, r]
    if (root == NULL) {
        return;
    }
    if (root->right != NULL) {
        if (strcmp(root->key, r_border) >= 0) {
            // no
        } else {
            print_tree(root->right, l_border, r_border);
        }
    }
    printf("%s: %s\n", root->key, root->val);

    if (root->left != NULL) {
        if (strcmp(root->key, l_border) <= 0) {
            //no
        } else {
            print_tree(root->left, l_border, r_border);
        }
    }
}



int insert(Node *new, Node **root) {
    if (*root == NULL) {
        (*root) = new;
        new->par = NULL;
        new->left = NULL;
        new->right = NULL;
        return SUCCESS;
    }
    int cmp = strcmp((*root)->key, new->key);
    if (cmp == 0) {
        return ALREADY_EXISTS;
    } else if (cmp < 0) {
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
    printf("iter\n");
    return insert(new, root);
}

int delete(Node **root, const char *key) {
    Node *target = find(*root, key);
    if (target == NULL) {
        return NOT_FOUND;
    }
    Node *par = target->par;
    if (target->left == NULL && target->right == NULL) {
        if (par == NULL) {
            *root = NULL;
        } else {
            if (strcmp(par->key, (*root)->key) > 0) { //  par
                par->left = NULL;//             target/
            } else {
                par->right = NULL;
            }
        }
    } else if (target->left == NULL) {
        if (par == NULL) {
            *root = target->right;
        } else {
            if (strcmp(par->key, (*root)->key) > 0) {
                par->left = target->right;
            } else {
                par->right = target->right;
            }
        }
    } else if (target->right == NULL) {
        if (par == NULL) {
            *root = target->left;
        } else {
            if (strcmp(par->key, (*root)->key) > 0) {
                par->left = target->left;
            } else {
                par->right = target->left;
            }
        }
    } else {
        // closest bigger
        Node *recipient = target->right;
        while (recipient != NULL)
        {
            recipient = recipient->left;
        }
        if (par == NULL) {
            *root = recipient;
        } else if (strcmp(par->key, (*root)->key) > 0) {
            par->left = recipient;
        } else {
            par->right = recipient;
        }
        recipient->left = target->left;
        recipient->right = target->right;
        recipient->par = par;
        
    }
    free_node(target);
    return SUCCESS;
}

Node *spec_find(Node *root, const char *border) {
    if (root == NULL) {
        return NULL;
    }
    int cmp = strcmp(root->key, border);
    if (cmp == 0) {
        return root;
    } else if (cmp > 0) {
        if (root->left == NULL) {
            return NULL;
        }
        return spec_find(root->left, border);
    } else {
        if (root->right == NULL) {
            return root;
        } else {
            if (strcmp(root->right->key, border) > 0) {
                return root;
            }
            return spec_find(root->right, border);
        }
    }
}
void free_node(Node *n) {
    if (n != NULL) {
        free(n->key);
        free(n->val);
        free(n);
    }
}

void free_tree(Node *root) {
    if (root == NULL) {
        return;
    }
    if (root->right != NULL) {
        free_tree(root->right);
    }
    if (root->left != NULL) {
        free_tree(root->left);
    }
    free_node(root);
}
