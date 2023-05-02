#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#include "interface.h"

int insert_opt(Node **root) {
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

int delete_opt(Node **root) {
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
    free(l_border);
    free(r_border);
}

int spec_find_opt(Node *root) {
    char *border = readline("Input right border: ");
    if (border == NULL) {
        return EOF;
    }
    Node *target = spec_find(root, border);
    if (target == NULL) {
        return NOT_FOUND;
    }
    printf("Best one is: key = %s, value = %s\n", target->key, target->val);
    free(border);
    return SUCCESS;
}

char *freadline(FILE *readfile) {
    char *ptr = (char *)malloc(1 * sizeof(char));
    char buf[256];

    int n, len = 0, buf_len;
    *ptr = '\0';
    do {
        n = fscanf(readfile, "%255[^\n]%n", buf, &buf_len);
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
        }
        if (n == 0)
            fscanf(readfile, "%*c");
        else {
            len += buf_len;
            ptr = (char *)realloc(ptr, (len + 1) * sizeof(char));
            strcat(ptr, buf);
        }
    } while (n > 0);
    return ptr;
}

int import_opt(Node **root) {
    char *filename = readline("Input name of file: ");
    if (filename == NULL) {
        return EOF;
    }
    FILE *readfile = fopen(filename, "r");
    free(filename);
    if (readfile == NULL){
        return ERR;
    }
    // printf("file opened\n"); // DEBUG
    char *marker;
    char *str_part = freadline(readfile);
    if (str_part == NULL) {
        return EOF;
    }
    int len = strtol(str_part, &marker, 10); 
    
    if (marker == str_part) { // bad str to long
        printf("File's length not found.\n");
        free(str_part);
        return ERR;
    } else if (len < 0) {
        printf("Bad number\n");
        free(str_part);
        return ERR;
    }
    free(str_part);

    // printf("%d\n", t->max_size); // DEBUG
    for (int i = 0; i < len; i++) {
        char *key = freadline(readfile);
        char *value = freadline(readfile);
        if (key == NULL) {
            break;
        }
        if (value == NULL) {
            free(key);
            break;
        }
        Node *new = malloc(sizeof(Node));
        new->key = key;
        new->val = value;
        int out = insert(new, root);
        if (out == ALREADY_EXISTS) {
            printf("Element No.%d already exists, won't be included in the table\n", i + 1);
            free(key);
            free(value);
        }
    }
    fclose(readfile);
    return SUCCESS;
}

void put_tree(Node *root, int level) {
	int i = level;
	if (root){
		put_tree(root->right, level + 1);
		while (i-- > 0)
			printf("  ");
		printf("%s\n", root->key);
		put_tree(root->left, level + 1
			);
	}
}