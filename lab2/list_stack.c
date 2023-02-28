#include "stack.h"
#include "list_stack.h"
#include <stdlib.h>

int push(Stack *s, Item *val) {
    val->next = s->top;
    s->top = val->next;
    return CORRECT_CODE;
}

int pop(Stack *s, Item *val) {
    if (s->top == NULL) {
        return ERR_CODE;
    }
    val = s->top;
    s->top = s->top->next;
    return CORRECT_CODE;
}

Stack *init(int len) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}