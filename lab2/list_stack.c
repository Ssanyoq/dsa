#include "list_stack.h"
#include <stdlib.h>
#include <stdio.h>


Stack *init(size_t len) { // top -> next -> next -> next -> NULL(bottom of a stack)
    Stack *s = (Stack *)malloc(sizeof(Stack));
    Item *first = (Item *)malloc(sizeof(Item));
    first->value = 0;
    s->head = first;
    Item *last = first;

    for (int i = 0; i < len - 1; i++) {
        Item *cur = (Item *)malloc(sizeof(Item));
        cur->value = 0;
        last->next = cur;
        last = cur;
    }
    last->next = NULL;

    return s;
}

Stack *push(Stack *s, Item *val) {
    val->next = s->head;
    s->head = val;
    return s;
}

Item pop(Stack *s) {
    Item *val = s->head;
    s->head = s->head->next;
    return *val;
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

void print_stack(Stack *a) { // for testing only, prints stack backwards
    Item *cur = a->head;
    while (cur != NULL)
    {
        printf("%d ", cur->value);
        cur = cur->next;
    }
    printf("\n");
}