#include "structs.h"
#include "interface.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>

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


int parse_file(Table *t, const char *path) {
    FILE *readfile = fopen(path, "r");
    if (readfile == NULL){
        return ERR_CODE;
    }
    printf("file opened\n"); // DEBUG
    char *marker;
    char *str_part = freadline(readfile);
    if (str_part == NULL) {
        return ERR_CODE;
    }
    int len = strtol(str_part, &marker, 10); 
    
    if (marker == str_part) { // bad str to long
        printf("File's length not found.\n");
        free(str_part);
        return ERR_CODE;
    } else if (len <= 0) {
        printf("Bad number\n");
        free(str_part);
        return ERR_CODE;
    }
    free(str_part);

    // printf("length before: %d\n", len); // FOR DEBUG
    t = (Table *)realloc(t, sizeof(Table));
    t->cur_len = 0;
    t->max_len = len;
    t->arr = (Item *)realloc(t->arr, sizeof(Item) * len);
    if (t->arr == NULL) {
        printf("Memory allocation error\n");
        return ERR_CODE;
    }
    
    int real_i = 0;
    int i = 0;
    for (; i < len; i++) {
        char *key = freadline(readfile);
        char *par_key = freadline(readfile);
        char *value = freadline(readfile);
        if (key == NULL) {
            break;
        }
        if (par_key == NULL) {
            free(key);
            break;
        }
        if (value == NULL) {
            free(key);
            free(par_key);
            break;
        }
        char *m;
        int k = strtol(key, &m, 10);
        if (m == key) { // bad str to long
            goto elem_err;
        } else if (k < 0) {
            goto elem_err;
        }

        int par_k = strtol(par_key, &m, 10);
        if (m == par_key) { // bad str to long
            goto elem_err;
        } else if (par_k < 0) {
            goto elem_err;
        }
        int out = insert(t, k, par_k, value);
        if (out == ALREADY_EXISTS) {
            elem_err:
            printf("Incorrect element No.%d, won't be included in the array\n", i + 1);
        }
        free(key);
        free(par_key);
        free(value);
        
    }
    fclose(readfile);
    // printf("len after: %d, i: %d, real i:%d, new_len: %d \n", len, i, real_i, new_len); // FOR DEBUG
    return SUCCESS;
}

int input_elem(Table *t) {
    if (t->max_len == t->cur_len) {
        return OVERFLOW;
    }
    printf("Input a new element:\n");
    char *key = readline("Key: ");
    if (key == NULL) {
        return EOF;
    }

    char *par_key = readline("Parent key: ");
    if (par_key == NULL) {
        free(key);
        return EOF;
    }
    char *value = readline("Value: ");
    if (value == NULL) {
        free(par_key);
        free(key);
        return EOF;
    }
    char *m;
    int k = strtol(key, &m, 10);
    if (m == key) { // bad str to long
        goto err;
    } else if (k < 0) {
        goto err;
    }

    int par_k = strtol(par_key, &m, 10);
    if (m == par_key) { // bad str to long
        goto err;
    } else if (par_k < 0) {
        err:
        free(key);
        free(par_key);
        free(value);
        return ERR_CODE;
    }

    if (insert(t, k, par_k, value) == ALREADY_EXISTS /* || find(par_k, out) == NULL || !check_value(value) */) {
        return ALREADY_EXISTS;
    }
    return SUCCESS;
}

int delete_elem(Table *t) {
    printf("Input key of an element that you want to delete: ");
    char *marker;
    char *str_part = readline("");
    if (str_part == NULL) {
        return EOF;
    }
    int key = strtol(str_part, &marker, 10); 
    if (marker == str_part) {
        free(str_part);
        return ERR_CODE; // no integers
    }
    free(str_part);
    return delete(t, key); 
}