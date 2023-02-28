#include "queue.h"
#include "list_queue.h"
#include <stdlib.h>

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