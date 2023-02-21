#include "list_stack.h"
#include <stdlib.h>
#include <stdio.h>


Stack *init(size_t len) { // top -> next -> next -> next -> NULL(bottom of a stack)
    // len for vector
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->head = NULL;
    return s;
}

int push(Stack *s, Item *val) {
    val->next = s->head;
    s->head = val;
    return 0;
}

Item *pop(Stack *s) {
    if (s->head == NULL) {
        return NULL;
    }
    Item *val = s->head;
    s->head = s->head->next;
    return val;
}

void free_stack(Stack *s) {
    Item *cur = s->head;
    Item *next = NULL;
    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    free(s);
}