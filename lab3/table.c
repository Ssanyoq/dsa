#include "structs.h"
#include "table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>


KeySpace *find(int key, Table *table) {
    for (int i = 0; i < table->cur_size; i++) {
        if (table->elems[i].key == key) {
            return &(table->elems[i]);
        }
    }
    return NULL;
}

int find_with_inputs(Table *t) {
    int out = 0;
    int key;
    char *str_part = readline("Input key of a desired element: ");
    char *marker;
    key = strtol(str_part, &marker, 10);
    if (str_part == marker) {
        return -1;
    }
    KeySpace *found = find(key, t);
    if (found == NULL) {
        printf("There is no such element with key = %d.\n", key);
    } else {
        printf("Found! Element:\nkey = %d, parent key = %d, value = %s\n", found->key, found->par_key, found->item->data);
    }
    return 1;
}

int add(Table *t, KeySpace *item) {
    if (find(item->key, t) != NULL || t->cur_size == t->max_size) {
        return -1;
    }
    t->elems[t->cur_size] = *item;
    t->cur_size++;
    return 1;
}

int input_elem(FILE *readfile, Table *t) {
    if (t->max_size == t->cur_size) {
        return -1;
    }
    printf("input a new element:\n");
    printf("Key: ");
    char *key = freadline(readfile);
    printf("Parent key: ");
    char *par_key = freadline(readfile);
    printf("Value: ");
    char *value = freadline(readfile);
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
        goto err;
    }

    if (find(k, t) != NULL /* || find(par_k, out) == NULL || !check_value(value) */) { //  TODO: decide
        err:
        free(key);
        free(par_key);
        free(value);
        return -1;
    }
    free(key);
    free(par_key);
    KeySpace new;
    new.key = k;
    new.par_key = par_k;
    new.item = (Item *)malloc(sizeof(Item));
    new.item->data = value;
    t->elems[t->cur_size] = new;
    t->cur_size++;
    return 1;
}

int delete_elem(Table *t) {
    printf("Input key of an element that you want to delete: ");
    char *marker;
    char *str_part = readline("");
    int key = strtol(str_part, &marker, 10); 
    if (marker == str_part) {
        return -1; // no integers
    }
    KeySpace *to_delete = find(key, t);
    if (to_delete == NULL) {
        return -1; // no such element
    }
    *to_delete = t->elems[t->cur_size - 1];
    t->cur_size--;
    return 1;
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

void print_table(Table *t) {
    printf("Table:\nMax length = %d\nCurrent length = %d\n", t->max_size, t->cur_size);
    for (int i = 0; i < t->cur_size; i++) {
        printf("key = %d; parent key = %d, data = %s\n", t->elems[i].key, t->elems[i].par_key, t->elems[i].item->data);
    }
}


Table *parse_file(char *path) {
    FILE *readfile = fopen(path, "r");
    char *marker;
    char *str_part = freadline(readfile);
    int len = strtol(str_part, &marker, 10); 
    
    if (marker == str_part) { // bad str to long
        printf("File's length not found.\n");
        return NULL;
    } else if (len <= 0) {
        printf("Bad number\n");
        return NULL;
    }
    free(str_part);

    // printf("length before: %d\n", len); // FOR DEBUG
    Table *out = (Table *)malloc(sizeof(Table));
    if (out == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    out->cur_size = len;
    out->max_size = len;
    out->elems = (KeySpace *)malloc(sizeof(KeySpace) * len);
    if (out == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    int real_i = 0;
    int i = 0;
    int new_len = len;
    for (; i < len; i++) {
        char *key = freadline(readfile);
        char *par_key = freadline(readfile);
        char *value = freadline(readfile);
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

        if (find(k, out) != NULL /* || find(par_k, out) == NULL || !check_value(value) */) { //  TODO: decide
            elem_err:
            printf("Incorrect element No.%d, won't be included in the array\n", i + 1);
            free(key);
            free(par_key);
            free(value);
            new_len--;
            continue;
        }
        free(key);
        free(par_key);
        KeySpace cur;
        cur.key = k;
        cur.par_key = par_k;
        cur.item = (Item *)malloc(sizeof(Item));
        cur.item->data = value;
        out->elems[real_i] = cur;
        real_i++;
    }
    if (i != real_i) {
        out->cur_size = new_len;
    }
    fclose(readfile);
    // printf("len after: %d, i: %d, real i:%d, new_len: %d \n", len, i, real_i, new_len); // FOR DEBUG
    return out;
}