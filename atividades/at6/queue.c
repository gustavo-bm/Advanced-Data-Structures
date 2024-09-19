#include <stdlib.h>
#include "queue.h"

void initialize(queue *q) {
    q->first = q->last = NULL;
}

void destroy(queue *q) {
    while(!empty(q))
        pop(q);
}

void* front(queue *q) {
    if(!empty(q))
        return q->first->data;
    return 0;
}

void push(queue *q, void* data) {
    qnode* novo = (qnode*)malloc(sizeof(qnode));
    novo->data = data;
    novo->next = NULL;
    if (empty(q)) {
        q->first = q->last = novo;
    } else {
        q->last->next = novo;
        q->last = novo;
    }
}

void pop(queue *q) {
    if (!empty(q)) {
        qnode* tmp = q->first;
        q->first = q->first->next;
        if (q->first == NULL) {
            q->last = NULL;
        }

        free(tmp);
    }
}


int empty(queue *q) {
    return q->first == 0;
}


