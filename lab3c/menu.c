#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#include "interface.h"

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

Table *import_table(const char *filename) {
    FILE *readfile = fopen(filename, "r");
    if (readfile == NULL){
        return NULL;
    }
    // printf("file opened\n"); // DEBUG
    char *marker;
    char *str_part = freadline(readfile);
    if (str_part == NULL) {
        return NULL;
    }
    int len = strtol(str_part, &marker, 10); 
    
    if (marker == str_part) { // bad str to long
        printf("File's length not found.\n");
        free(str_part);
        return NULL;
    } else if (len < 0) {
        printf("Bad number\n");
        free(str_part);
        return NULL;
    }
    free(str_part);

    Table *t = table_init(len);
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
        int out = insert(t, key, value);
        if (out == ALREADY_EXISTS) {
            printf("Element No.%d already exists, won't be included in the table\n", i + 1);
            free(key);
            free(value);
        } else {
            t->cur_size++;
        }
    }
    fclose(readfile);
    // printf("File closed\n");
    return t;
}

//
//
// menu options are below
//

int insert_opt(Table *t) {
    char *key = readline("Input key: ");
    if (key == NULL) {
        return EOF;
    }
    char *info = readline("Input value: ");
    if (info == NULL) {
        free(key);
        return EOF;
    }
    int out = insert(t, key, info);
    free(key);
    free(info);
    return out;
}

int delete_opt(Table *t) {
    char *key = readline("Input key: ");
    if (key == NULL) {
        return EOF;
    }
    int out = delete(t, key);
    free(key);
    return out;
}

int find_opt(const Table *t) {
    char *key = readline("Input key: ");
    if (key == NULL) {
        return EOF;
    }
    int out = find(t, key);
    free(key);
    if (out < 0) {
        return out;
    }
    printf("Element found!\nkey = %s, info = %s, busy = %d\n", 
        t->arr[out].key, t->arr[out].info, t->arr[out].busy);
    return SUCCESS;
}

int import_table_opt(Table **t) {
    char *filename = readline("Input path to the import file: ");
    if (filename == NULL) {
        return EOF;
    }
    Table *out = import_table(filename);
    free(filename);
    if (out == NULL) {
        return ERR;
    }
    free_table(*t);
    *t = out;
    return SUCCESS;
}
