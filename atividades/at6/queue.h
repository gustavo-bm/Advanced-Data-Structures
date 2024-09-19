#ifndef QUEUE_H
#define QUEUE_H

typedef struct qnode_ {
    void* data;
    struct qnode_ *next;
} qnode;

typedef struct {
    qnode *first, *last;
} queue;

void initialize(queue *q);

void destroy(queue *q);

void* front(queue *q);

void push(queue *q, void* data);

void pop(queue *q);

int empty(queue *q);

#endif