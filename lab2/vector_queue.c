#include "vector_queue.h"
#include "queue.h"

int push(Queue *q, Item *val) {
    if (q->tail == q->head - 1) {
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
    *val = q->arr[q->head];
    q->head++;
    return CORRECT_CODE;
}

Stack *init(int len) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->arr = (Item *)malloc(len * sizeof(Item));
    q->head = 0;
    q->tail = 0;
    q->max_size = len;
    return q;
}