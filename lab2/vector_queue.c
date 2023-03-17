#include "vector_queue.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

int push(Queue *q, Item *val) {
    if ((q->tail + 1) % q->max_size == q->head) {
        printf("Limit reached, new element(id = %s) won't be added\n", val->id);
        return ERR_CODE;
    }
    q->arr[q->tail] = *val;
    q->tail = (q->tail + 1) % q->max_size;
    return CORRECT_CODE;
}

int pop(Queue *q, Item *val) {
    if (q->head == q->tail) { 
        return ERR_CODE;
    }
    Item cur = q->arr[q->head]; 
    val = &cur;
    q->head++;
    return CORRECT_CODE;
}

Queue *init(int len) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->arr = (Item *)malloc(len * sizeof(Item));
    q->head = 0;
    q->tail = 0;
    q->max_size = len;
    return q;
}

Item *check(Queue *q) {
    if (q->head == q->tail) {
        return NULL;
    }
    return &(q->arr[q->head]);
}

void print_queue(Queue *q) {
    // printf("head=%d, tail=%d\n", q->head, q->tail);
    for (int i = q->head; i != q->tail || i >= q->max_size; i = (i + 1) % q->max_size) {
        printf("%s ", q->arr[i].id);
    }
    if ( q->arr[q->tail].id != NULL) {
        printf("%s", q->arr[q->tail].id);
    }
    printf("\n");
}