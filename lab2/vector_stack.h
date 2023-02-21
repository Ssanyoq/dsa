#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct Item
{
    char *id;
    int ta;
    int ts;
} Item;

typedef struct Stack
{
    int top;
    Item *arr;
} Stack;

Stack *init(size_t len);

int push(Stack *s, Item *val);

Item *pop(Stack *s);

void free_stack(Stack *s);

Stack *input_stack(Stack *s);

#endif