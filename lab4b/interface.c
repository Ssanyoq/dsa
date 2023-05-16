#include "interface.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

short get_color(const Node *p)
{
    if (p == NULL)
    {
        return BLACK;
    }
    return p->color;
}

Node *get_uncle(Node *target)
{
    if (target->par == NULL)
    {
        return NULL; // target - root
    }
    Node *gp = target->par->par;
    if (gp == NULL)
    {
        return NULL; // target->par - root
    }
    if (gp->left == target->par)
    {
        return gp->right;
    }
    else
    {
        return gp->left;
    }
}

Node *create_node()
{
    Node *creation = malloc(sizeof(Node));
    creation->left = NULL;
    creation->right = NULL;
    creation->par = NULL;
    creation->color = -1; // чтобы не забыть
    return creation;
}

// Function performing right rotation
// of the passed node
Node *rotate_right(Node *temp, Node *root)
{
    Node *left = temp->left;
    temp->left = left->right;
    if (temp->left)
        temp->left->par = temp;
    left->par = temp->par;
    if (!temp->par)
        root = left;
    else if (temp == temp->par->left)
        temp->par->left = left;
    else
        temp->par->right = left;
    left->right = temp;
    temp->par = left;
    return root;
}

// Function performing left rotation
// of the passed node
Node *rotate_left(Node *temp, Node *root)
{
    Node *right = temp->right;
    temp->right = right->left;
    if (temp->right)
        temp->right->par = temp;
    right->par = temp->par;
    if (!temp->par)
        root = right;
    else if (temp == temp->par->left)
        temp->par->left = right;
    else
        temp->par->right = right;
    right->left = temp;
    temp->par = right;
    return root;
}

void insertion_fixup(Node *root, Node *z)
{
    while (z->par->color == RED)
    {
        if (z->par == z->par->par->left)
        { // z.parent is the left child

            Node *y = z->par->par->right; // uncle of z

            if (get_color(y) == RED)
            { // case 1
                z->par->color = BLACK;
                y->color = BLACK;
                z->par->par->color = RED;
                z = z->par->par;
            }
            else
            { // case2 or case3
                if (z == z->par->right)
                {                  // case2
                    z = z->par; // marked z.parent as new z
                    root = rotate_left(z, root);
                }
                // case3
                z->par->color = BLACK;       // made parent black
                z->par->par->color = RED; // made parent red
                root = rotate_right(z->par->par, root);
            }
        }
        else
        {                                           // z.parent is the right child
            Node *y = z->par->par->left; // uncle of z

            if (get_color(y) == RED)
            {
                z->par->color = BLACK;
                y->color = BLACK;
                z->par->par->color = RED;
                z = z->par->par;
            }
            else
            {
                if (z == z->par->left)
                {
                    z = z->par; // marked z.parent as new z
                    root = rotate_right(z, root);
                }
                z->par->color = BLACK;       // made parent black
                z->par->par->color = RED; // made parent red
                root = rotate_left(z->par->par, root);
            }
        }
    }
    root->color = BLACK;
}

int insert(Node **root, Node *z)
{
    Node *y = NULL; // variable for the parent of the added node
    Node *temp = *root;

    while (temp != NULL)
    {
        y = temp;
        if (z->key < temp->key)
            temp = temp->left;
        else
            temp = temp->right;
    }
    z->par = y;

    if (y == NULL)
    { // newly added node is root
        *root = z;
    }
    else if (z->key < y->key) // data of child is less than its parent, left child
        y->left = z;
    else
        y->right = z;

    z->right = NULL;
    z->left = NULL;

    insertion_fixup(*root, z);
    return SUCCESS;
}

Node *rb_transplant(Node *root, Node *u, Node *v)
{
    if (u->par == NULL)
        root = v;
    else if (u == u->par->left)
        u->par->left = v;
    else
        u->par->right = v;
    v->par = u->par;
    return root;
}

Node *minimum(Node *root, Node *x)
{
    while (x->left != NULL)
        x = x->left;
    return x;
}

void rb_delete_fixup(Node *root, Node *x)
{
    while (x != root && get_color(x) == BLACK)
    {
        if (x == x->par->left)
        {
            Node *w = x->par->right;
            if (get_color(w) == RED)
            {
                w->color = BLACK;
                x->par->color = RED;
                root = rotate_left(x->par, root);
                w = x->par->right;
            }
            if (get_color(w->left) == BLACK && get_color(w->right) == BLACK)
            {
                w->color = RED;
                x = x->par;
            }
            else
            {
                if (get_color(w->right) == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    root = rotate_right(w, root);
                    w = x->par->right;
                }
                w->color = get_color(x->par);
                x->par->color = BLACK;
                w->right->color = BLACK;
                root = rotate_left(x->par, root);
                x = root;
            }
        }
        else
        {
            Node *w = x->par->left;
            if (get_color(w) == RED)
            {
                w->color = BLACK;
                x->par->color = RED;
                root = rotate_right(x->par, root);
                w = x->par->left;
            }
            if (get_color(w->right) == BLACK && get_color(w->left) == BLACK)
            {
                w->color = RED;
                x = x->par;
            }
            else
            {
                if (get_color(w->left) == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    root = rotate_left(w, root);
                    w = x->par->left;
                }
                w->color = get_color(x->par);
                x->par->color = BLACK;
                w->left->color = BLACK;
                root = rotate_right(x->par, root);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

int delete(Node **root, unsigned int key)
{
    Node *z = find(*root, key);
    if (z == NULL) {
        return NOT_FOUND;
    }

    Node *y = z;
    Node *x;
    int y_orignal_color = get_color(y);
    if (z->left == NULL)
    {
        x = z->right;
        *root = rb_transplant(*root, z, z->right);
    }
    else if (z->right == NULL)
    {
        x = z->left;
        *root = rb_transplant(*root, z, z->left);
    }
    else
    {
        y = minimum(*root, z->right);
        y_orignal_color = get_color(y);
        x = y->right;
        if (y->par == z)
        {
            x->par = z;
        }
        else
        {
            *root = rb_transplant(*root, y, y->right);
            y->right = z->right;
            y->right->par = y;
        }
        *root =rb_transplant(*root, z, y);
        y->left = z->left;
        y->left->par = y;
        y->color = z->color;
    }
    if (y_orignal_color == BLACK)
        rb_delete_fixup(*root, x);
    return SUCCESS;
}

Node *find(Node *root, unsigned int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->key == key)
    {
        return root;
    }
    else if (root->key < key)
    {
        root = root->right;
    }
    else
    {
        root = root->left;
    }
    return find(root, key);
}

Node *find_smallest(Node *root, unsigned left_border)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->key <= left_border && root->right != NULL)
    {
        root = root->right;
    }
    else if (root->left != NULL)
    {
        if (root->left->key <= left_border && root->left->right == NULL)
        {
            return root;
        }
        else
        {
            root = root->left;
        }
    }
    else if (root->key > left_border && root->right == NULL && root->left == NULL)
    {
        return root;
    }
    else
    {
        return NULL;
    }
    return find_smallest(root, left_border);
}

void print_in_order(Node *root, unsigned int left_border, short is_border)
{
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return;
    }
    if (root->right != NULL)
    {
        print_in_order(root->right, left_border, is_border);
    }

    if (root->key > left_border || !is_border)
    {
        if (root->color == RED)
        {
            printf("\033[0;31m"); // sets red
        }
        else if (root->color != BLACK)
        {
            printf("\033[0;35m"); // purple
            // printf("\033[0;30m"); // grey
        }
        printf("%u: %u\n", root->key, root->val);
        printf("\033[0m"); // resets color

        if (root->left != NULL)
        {
            print_in_order(root->left, left_border, is_border);
        }
    }
}

#define STEP 2

void print_tree(const Node *root, int level)
{
    /*
        white -> node is black
        red -> node is red
        purple -> node has incorrect color
    */
    int i = level;
    if (root)
    {
        print_tree(root->right, level + STEP);
        while (i-- > 0)
            printf("  ");

        if (root->color == RED)
        {
            printf("\033[0;31m"); // sets red
        }
        else if (root->color != BLACK)
        {
            printf("\033[0;35m"); // purple
            // printf("\033[0;30m"); // grey
        }
        printf("%u\n", root->key);
        printf("\033[0m"); // resets color
        print_tree(root->left, level + STEP);
    }
    else
    {
        while (i-- > 0)
            printf("  ");
        // printf("\033[0;30m");
        printf("nil\n");
        // printf("\033[0m");
    }
}

void free_node(Node *node)
{
    free(node);
}

void free_tree(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL)
    {
        free_tree(root->left);
    }
    if (root->right != NULL)
    {
        free_tree(root->right);
    }
    free(root);
}
