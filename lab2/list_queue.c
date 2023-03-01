#include "queue.h"
#include "list_queue.h"
#include <stdlib.h>
#include <stdio.h>

int push(Queue *q, Item *val) {
    Item *new = (Item *)malloc(sizeof(Item));
    new = val;
    val->next = NULL;
    if (q->head == NULL) {
        q->head = new;
        q->tail = new;
    } else {
        q->tail->next = new;
        q->tail = q->tail->next;
    }
    return EXIT_SUCCESS;
}

int pop(Queue *q, Item *val) {
    if (q->head == NULL) {
        return ERR_CODE;
    }
    val = q->head;
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    return EXIT_SUCCESS;
}

Queue *init(int len) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

Item *check(Queue *q) {
    return q->head;
}

void print_queue(Queue *q) {
    Item *cur = q->head;
    while (cur != q->tail)
    {
        printf("%s ", cur->id);
        cur = cur->next;
    }
    if (cur != NULL) {
        printf("%s", cur->id);
    }
    printf("\n");
}