#include "interface.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


static int hash_string(const char *s) {
    int out = 0;
    for (int i = 0; i < strlen(s); i++) {
        out += s[i];
    }
    return out;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int get_index(const char *key, int size) {
    int hash = hash_string(key);
    return hash % size;
}

Table *table_init(int size) {
    Table *new = (Table *)malloc(sizeof(Table));
    new->max_size = size;
    new->cur_size = 0;
    new->arr = (KeySpace *)malloc(sizeof(KeySpace) * new->max_size);
    for (int i = 0; i < size; i++) {
        new->arr[i].busy = 0;
    }
    return new;
}

int find(const Table *t, const char *key) {
    int index = get_index(key, t->max_size);
    int amt_passed = 0;
    while (amt_passed < t->max_size)
    {
        if (t->arr[index].busy) {
            if (strcmp(t->arr[index].key, key) == 0) {
                return index;
            }
        }
        index = (index + 1) % t->max_size;
        amt_passed++;
    }
    return NOT_FOUND;
}

int insert(const Table *t, char *key, char *info) {
    if (t->cur_size == t->max_size) {
        return TABLE_OVERFLOW;
    }
    if (find(t, key) != NOT_FOUND) {
        return ALREADY_EXISTS;
    }
    int index = get_index(key, t->max_size);
    int amt_passed = 0;
    while (amt_passed < t->max_size) {
        if (!t->arr[index].busy) {
            t->arr[index].info = info;
            t->arr[index].key = key;
            t->arr[index].busy = 1;
            return SUCCESS;
        }
        index = (index + 1) % t->max_size;
        amt_passed++;
    }
    return ERR; // bad bad bad
}

int delete(const Table *t, const char *key) {
    int index = find(t, key);
    if (index == NOT_FOUND) {
        return NOT_FOUND;
    }
    free(t->arr[index].info);
    free(t->arr[index].key);
    t->arr[index].busy = 0;
    return SUCCESS;
}

static void print_separator(int size) {
    for (int i = 0; i < size; i++) {
        printf("-");
    }
    printf("\n");
}

void print_table(const Table *t) {
    /*  max len = x, cur len = y      
       |key   |  value       |  busy  |
               ...
    */
    int max_key = 3 + 2; // " key "
    int max_val = 5 + 2; // " value "
    for (int i = 0; i < t->max_size; i++) {
        int cur_key, cur_val;
        if (t->arr[i].key == NULL) {
            cur_key = 4 + 2;
        } else {
            cur_key = strlen(t->arr[i].key) + 2;
        }
        if (t->arr[i].info == NULL) {
            cur_val = 4 + 2;
        } else {
            cur_val = strlen(t->arr[i].info) + 2; 
        }
        max_key = max(max_key, cur_key);
        max_val = max(max_val, cur_val);
    }
    // |<max_val>|<max_key>|<4>|
    int width = 1 + max_val + 1 + max_key + 1 + 4 + 1;
    printf(" Table: max length = %d, current length = %d\n", t->max_size, t->cur_size);
    print_separator(width);
    printf("| %-*s| %-*s|busy|\n",max_key - 1, "key", max_val - 1, "value");
    print_separator(width);

    for (int i = 0; i < t->max_size; i++) {
        if (t->arr[i].key == NULL) {
            printf("| %-*s|", max_key - 1, "NULL");
        } else {
            printf("| %-*s|", max_key - 1, t->arr[i].key);
        }
        if (t->arr[i].info == NULL) {
            printf(" %-*s|", max_val - 1, "NULL");
        } else {
            printf(" %-*s|", max_val - 1, t->arr[i].info);
        }
        printf(" %d  |\n", t->arr[i].busy);
        print_separator(width);
    }
}


void free_table(Table *t) {
    for (int i = 0; i < t->max_size; i++) {
        if (t->arr[i].busy == 1) {
            free(t->arr[i].info);
            free(t->arr[i].key);
        }
    }
    free(t->arr);
    free(t);
}