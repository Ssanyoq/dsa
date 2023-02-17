#ifndef LIST_STACK_H
#define LIST_STACK_H

#include <stddef.h>

typedef struct Item {
    char *id;
    int ta;
    int ts;
    struct Item *next;
} Item;

typedef struct Stack
{
    struct Item *head;
} Stack;

Stack *init(size_t len);

int push(Stack *s, Item *val);

Item *pop(Stack *s);

void free_stack(Stack *s);

#endif