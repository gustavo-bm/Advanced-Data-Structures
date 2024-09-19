#include <stdio.h>
#include <stdlib.h>
#include "filaPrioridade.h"

// inicia o heap
void inicializarFila(FilaPrioridade *heap, int capacity) {
    heap->data = (int *)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
}

// insere um valor no heap
void inserirFila(FilaPrioridade *heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap está cheio!\n");
        return;
    }
    int i = heap->size++;
    while (i > 0 && heap->data[(i - 1) / 2] > value) {
        heap->data[i] = heap->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->data[i] = value;
}

// remove o menor valor do heap
int retirarFila(FilaPrioridade *heap) {
    if (heap->size == 0) {
        return -1;
    }

    int minValue = heap->data[0];
    int temp = heap->data[--heap->size];
    int i = 0, child;

    while (2 * i + 1 < heap->size) {
        child = 2 * i + 1;
        if (child + 1 < heap->size && heap->data[child + 1] < heap->data[child]) {
            child++;
        }
        if (temp <= heap->data[child]) {
            break;
        }
        heap->data[i] = heap->data[child];
        i = child;
    }
    heap->data[i] = temp;
    return minValue;
}

int vazia(FilaPrioridade *heap) {
    return heap->size == 0;
}

void liberar(FilaPrioridade *heap) {
    free(heap->data);
}
