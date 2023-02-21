#include "vector_stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#define LIMIT 1000

Stack *init(size_t len) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = 0;
    s->arr = (Item *)malloc(len * sizeof(Item));
    return s;
}

Stack *input_stack(Stack *s, int *stands) {
    Stack s[LIMIT];    
    char *str;
    str = readline("");
    *stands = -1;    
    while (str != NULL)
    {
        char *word = strtok(str, " \t");
        while (str != NULL) {
            if (*stands == -1) {
                char *tmp;
                *stands = strtol(word, tmp, 10);
                continue;
            }

            Item new;
            char *part = strtok(word, "/");
            new.id = part;
            part = strtok()
        }
    }
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

void print_stack(Stack *s) {
}