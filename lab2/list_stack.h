#ifndef STACK_H
#define STACK_H

typedef struct Item {
    int value;
    struct Item *next;
} Item;

typedef struct
{
    struct Item *head;
} Stack;

#endif