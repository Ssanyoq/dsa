#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "interface.h"

int table_init(Table *t, const char *filename) {
    FILE *fd = fopen(filename, "rb+wb");
    if (fd == NULL) {
        return ERR_CODE;
    }
    t = (Table *)malloc(sizeof(Table));
    t->cur_len = 0;
    t->max_len = 0;
    t->fd = fd;
    t->arr = (Item *)malloc(t->max_len * sizeof(Item));
    return SUCCESS;
}


int find(const Table *t, int key) {
    for (int i = 0; i < t->cur_len; i++) {
        if (t->arr[i].key == key) {
            return i;
        }
    }
    return NOT_FOUND;
}

int insert(Table *t, int key, int par_key, const char *str) {
    if (find(t, key) != NOT_FOUND) {
        return ALREADY_EXISTS;
    }
    if (t->max_len == t->cur_len) {
        return OVERFLOW;
    }
    t->arr[t->cur_len].key = key;
    t->arr[t->cur_len].par_key = par_key;
    t->arr[t->cur_len].len = strlen(str) + 1;

    fseek(t->fd, 0, SEEK_END);
    t->arr[t->cur_len].offset = ftell(t->fd);
    fwrite(str, sizeof(char), t->arr[t->cur_len].len, t->fd);
    t->cur_len++;
    return SUCCESS;
}

int delete(Table *t, int key) {
    int index = find(t, key);
    if (index == NOT_FOUND) {
        return NOT_FOUND;
    }
    int delta = t->arr[index].len;
    char *buf = (char *)malloc(sizeof(char));
    for (int i = index + 1; i < t->cur_len; i++) {
        buf = (char *)realloc(buf, sizeof(char) * t->arr[i].len);
        fseek(t->fd, t->arr[i].offset, SEEK_SET);
        fread(buf, sizeof(char), t->arr[i].len, t->fd);
        t->arr[i].offset -= delta;
        fseek(t->fd, t->arr[i].offset, SEEK_SET);
        fwrite(buf, sizeof(char), t->arr[i].len, t->fd);
    }
    free(buf);
    return SUCCESS;
}

void print_table(Table *t) {
    printf("Table: max size = %d, current size = %d\n", t->max_len, t->cur_len);
    char *buf = (char *)malloc(sizeof(char));
    for (int i = 0; i < t->cur_len; i++) {
        fseek(t->fd, t->arr[i].offset, SEEK_SET);
        buf = (char *)malloc(t->arr[i].len * sizeof(char));
        fread(buf, sizeof(char), t->arr[i].len, t->fd);
        printf("key: %d; parent key: %d; value: %s\n", t->arr[i].key, t->arr[i].par_key, buf);
    }
    free(buf);
}

int save_table(Table *t, const char *filename) {
    FILE *savefile = fopen(filename, "w");
    if (savefile == NULL) {
        return ERR_CODE;
    }
    char *buf = (char *)malloc(sizeof(char));
    
    fprintf("%d\n", t->max_len);

    for (int i = 0; i < t->cur_len; i++) {
        fseek(t->fd, t->arr[i].offset, SEEK_SET);
        buf = (char *)malloc(t->arr[i].len * sizeof(char));
        fread(buf, sizeof(char), t->arr[i].len, t->fd);

        fprintf("%d\n%d\n%s\n", t->arr[i].key, t->arr[i].par_key, buf);
    }
    free(buf);
    return SUCCESS;
}

void free_table(Table *t) {
    fclose(t->fd);
    free(t->arr);
    free(t);
}