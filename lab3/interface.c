#include "table.h"
#include "interface.h"
#include <stdlib.h>


int add(Table *t, KeySpace *item) {
    if (find(item->key, t) != NULL || t->cur_size == t->max_size) {
        return ERR_CODE;
    }
    t->elems[t->cur_size] = *item;
    t->cur_size++;
    return 1;
}

KeySpace *find(int key, Table *table) {
    for (int i = 0; i < table->cur_size; i++) {
        if (table->elems[i].key == key) {
            return &(table->elems[i]);
        }
    }
    return NULL;
}

KeySpace **find_children(int key, Table *t, int *size) {
    // returns array with elems that have par_key == key
    KeySpace **children = (KeySpace **)malloc(sizeof(KeySpace *) * t->cur_size);
    int children_amt = 0;
    for (int i = 0; i < t->cur_size; i++) {
        if (t->elems[i].par_key == key) {
            children[children_amt] = &(t->elems[i]);
            children_amt++;
        }
    }
    children = (KeySpace **)realloc(children, sizeof(KeySpace) * children_amt);
    *size = children_amt;
    return children;
}

int delete(Table *t, int key) {
    KeySpace *to_delete = find(key, t);
    if (to_delete == NULL) {
        return ERR_CODE; // no such element
    }
    *to_delete = t->elems[t->cur_size - 1];
    t->cur_size--;
    free_ks(t->elems[t->cur_size]);
    return 1;
}

void free_table(Table *t) {
    if (t == NULL) {
        return;
    }
    for (int i = 0; i < t->cur_size; i++) {
        free_ks(t->elems[i]);
    }
    free(t->elems);
    free(t);
}

