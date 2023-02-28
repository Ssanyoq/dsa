#include "vector_stack.h"
#include "stack.h"

int push(Stack *s, Item *val) {
    if (s->max_size == s->top) {
        return ERR_CODE;
    }
    (s->arr)[s->top] = *val;
    s->top++;
    return CORRECT_CODE;
}

int pop(Stack *s, Item *val) {
    if (s->top == 0) {
        return ERR_CODE;
    }
    *val = (s->arr)[s->top - 1];
    s->top--;
    return CORRECT_CODE;
}

Stack *init(int len) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->max_size = len - 1;
    s->top = 0;
    s->arr = (Item *)malloc(len * sizeof(Item));
    return s;
}