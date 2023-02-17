#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct Item
{
    int val;
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

void print_stack(Stack *a); // debug purpose

#endif