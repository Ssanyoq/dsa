#ifndef LIST_STACK_H
#define LIST_STACK_H

#include <stddef.h>

typedef struct Item {
    int value;
    struct Item *next;
} Item;

typedef struct Stack
{
    struct Item *head;
} Stack;

Stack *init(size_t len);

Stack *push(Stack *s, Item *val);

Item pop(Stack *s);

void free_stack(Stack *s);

void print_stack(Stack *a); // debug purpose

#endif