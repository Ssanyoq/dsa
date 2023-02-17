#include "vector_stack.h"
#include <stdlib.h>

Stack *init(size_t len) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = 0;
    s->arr = (Item *)malloc(len * sizeof(Item));
    return s;
}

int push(Stack *s, Item *val) {
    s->arr[s->top] = *val;
    s->top += 1;
    return 0;
}

Item *pop(Stack *s){
    if (s->top == 0) {
        return NULL;
    }
    s->top -= 1;
    return &(s->arr[s->top + 1]);
}

void free_stack(Stack *s) {
    free(s->arr);
    free(s);
}   

void print_stack(Stack *a) {
    for (int i = 0; i < a->top; i++) { 
        printf("%d ", a->arr[i]);
    }
    printf("\n");
}