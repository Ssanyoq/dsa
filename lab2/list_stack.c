#include "list_stack.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdio.h"


Stack *init(size_t len) {
    Stack *s = (Stack *)malloc(len * sizeof(Item));
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

void print_stack(Stack *a) {
    Item *cur = a->head;
    while (cur != NULL)
    {
        printf("%d ", cur->value);
        cur = cur->next;
    }
    printf("\n");
}

int main() {
    Stack *s = init(100);
    print_stack(s);
}