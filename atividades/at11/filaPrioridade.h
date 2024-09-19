#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

typedef struct {
    int *data;  
    int size;   
    int capacity;  
} FilaPrioridade;

void inicializarFila(FilaPrioridade *heap, int capacity);
void inserirFila(FilaPrioridade *heap, int value);
int retirarFila(FilaPrioridade *heap);
int vazia(FilaPrioridade *heap);
void liberar(FilaPrioridade *heap);

#endif
