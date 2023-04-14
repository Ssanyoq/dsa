#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "interface.h"

int table_init(Table **t, const char *descriptor_path, const char *values_path, const char *memory_path) {
    /*
    descriptor:
    <len>
    <key>
    <par_key>
    <offset>
    <len>
    -//-
    */
    FILE *fd = fopen(memory_path, "rb+"); // memory
    if (fd == NULL) {
        return ERR_CODE;
    }
    FILE *save = fopen(descriptor_path, "rb"); // descriptor
    if (save == NULL) {
        fclose(fd);
        return ERR_CODE;
    }
    FILE *vals = fopen(values_path, "rb"); // values
    fseek(save, 0, SEEK_SET);
    int len;
    int out = fread(&len, sizeof(int), 1, save);
    *t = (Table *)malloc(sizeof(Table));
    (*t)->cur_len = 0;
    (*t)->max_len = 0;
    (*t)->fd = fd;
    (*t)->arr = (Item *)malloc((*t)->max_len * sizeof(Item));
    if (out != sizeof(int)) {
        (*t)->max_len = len;
        (*t)->arr = (Item *)realloc((*t)->arr, len * sizeof(Item));
        int key, par_key, offset, val_len;
        for (int i = 0; i < len; i++) {
            out = fread(&key, sizeof(int), 1, save);
            if (out != 1) {
                break;
            }
            out = fread(&par_key, sizeof(int), 1, save);
            if (out != 1) {
                break;
            }
            out = fread(&offset, sizeof(int), 1, save);
            if (out != 1) {
                break;
            }
            out = fread(&val_len, sizeof(int), 1, save);
            if (out != 1) {
                break;
            }
            (*t)->arr[i].key = key;
            (*t)->arr[i].par_key = par_key;
            (*t)->arr[i].offset = offset;
            (*t)->arr[i].len = val_len;
            (*t)->cur_len++;
        }
    }
    fseek(vals, 0, SEEK_SET);
    char *buf = (char *)malloc(sizeof(char) * 512);
    while (1)
    {   
        out = fread(buf, sizeof(char), 512, vals);
        if (out == 0) {
            break;
        }
        fwrite(buf, sizeof(char), out, fd);
    }
    free(buf);
    fclose(save);
    fclose(vals);
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
    int delta = t->arr[index].len * sizeof(char);
    char *buf = (char *)malloc(sizeof(char));
    for (int i = index + 1; i < t->cur_len; i++) {
        buf = (char *)realloc(buf, sizeof(char) * t->arr[i].len);
        fseek(t->fd, t->arr[i].offset, SEEK_SET);
        fread(buf, sizeof(char), t->arr[i].len, t->fd);
        t->arr[i].offset -= delta;
        fseek(t->fd, t->arr[i].offset, SEEK_SET);
        fwrite(buf, sizeof(char), t->arr[i].len, t->fd);
        t->arr[i - 1] = t->arr[i];
    }
    t->cur_len--;
    free(buf);
    return SUCCESS;
}

void print_table(const Table *t) {    
    printf("Table: max size = %d, current size = %d\n", t->max_len, t->cur_len);
    char *buf;
    for (int i = 0; i < t->cur_len; i++) {
        fseek(t->fd, t->arr[i].offset, SEEK_SET);
        buf = (char *)malloc(t->arr[i].len * sizeof(char));
        fread(buf, sizeof(char), t->arr[i].len, t->fd);
        printf("key: %d; parent key: %d; value: %s\n", t->arr[i].key, t->arr[i].par_key, buf);
        free(buf);
    }
}

int save_table(const Table *t, const char *filename, const char *vals_path) {
    FILE *savefile = fopen(filename, "wb");
    if (savefile == NULL) {
        return ERR_CODE;
    }
    fseek(savefile, 0, SEEK_SET);
    fwrite(&(t->max_len), sizeof(int), 1, savefile);
    for (int i = 0; i < t->cur_len; i++) {
        fwrite(&(t->arr[i].key), sizeof(int), 1, savefile);
        fwrite(&(t->arr[i].par_key), sizeof(int), 1, savefile);
        fwrite(&(t->arr[i].offset), sizeof(int), 1, savefile);
        fwrite(&(t->arr[i].len), sizeof(int), 1, savefile);
    }
    fclose(savefile);
    FILE *vals = fopen(vals_path, "wb");
    char *buf = (char *)malloc(sizeof(char) * 512);
    int out;
    fseek(t->fd, 0, SEEK_SET);
    fseek(vals, 0, SEEK_SET);
    while (1)
    {   
        out = fread(buf, sizeof(char), 512, t->fd);
        if (out == 0) {
            break;
        }
        fwrite(buf, sizeof(char), out, vals);
    }
    fclose(vals);
    free(buf);
    return SUCCESS;
}

void free_table(Table *t) {
    fclose(t->fd);
    free(t->arr);
    free(t);
}

char *get_val(const Table *t, int key) {
    int index = find(t, key);
    if (index == NOT_FOUND) {
        return NULL;
    }
    fseek(t->fd, t->arr[index].offset, SEEK_SET);
    char *buf = (char *)malloc(t->arr[index].len * sizeof(char));
    fread(buf, sizeof(char), t->arr[index].len, t->fd);
    return buf;
}

int *find_children(const Table *t, int par_key, int *len) {
    int *out = (int *)malloc(t->cur_len * sizeof(int)); // worst scenario
    *len = 0;
    for (int i = 0; i < t->cur_len; i++) {
        if (t->arr[i].par_key == par_key) {
            out[*len] = i;
            (*len)++;
        }
    }
    out = (int *)realloc(out, sizeof(int) * (*len));
    return out;
}
