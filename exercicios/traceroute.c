#include <stdio.h>
#include <stdlib.h>

#define INFINITO 1000000

typedef struct node {
    int v;           // Vértice adjacente
    struct node *next; // Próximo vértice na lista
} *link;

typedef struct {
    int V;    // Número de vértices
    int A;    // Número de arestas
    link *adj; // Lista de adjacências
} g_list;

typedef struct {
    int *data;
    int front, rear, size, capacity;
} Fila;

void inicializaFila(Fila *f, int capacidade) {
    f->data = (int *)malloc(capacidade * sizeof(int));
    f->front = 0;
    f->rear = capacidade - 1;
    f->size = 0;
    f->capacity = capacidade;
}

int filaVazia(Fila *f) {
    return (f->size == 0);
}

void enfileira(Fila *f, int valor) {
    f->rear = (f->rear + 1) % f->capacity;
    f->data[f->rear] = valor;
    f->size = f->size + 1;
}

int desenfileira(Fila *f) {
    int valor = f->data[f->front];
    f->front = (f->front + 1) % f->capacity;
    f->size = f->size - 1;
    return valor;
}

int tamanho(g_list *g, int origem, int destino) {
    if (origem == destino) return 0;  // se origem e destino são o mesmo

    int *dist = (int *)malloc(g->V * sizeof(int));
    for (int i = 0; i < g->V; i++) {
        dist[i] = INFINITO;  // inicializa todas as distâncias como infinito
    }

    Fila f;
    inicializaFila(&f, g->V);

    dist[origem] = 0;
    enfileira(&f, origem);

    while (!filaVazia(&f)) {
        int v = desenfileira(&f);

        // percorre os adjacentes de 'v'
        for (link n = g->adj[v]; n != NULL; n = n->next) {
            if (dist[n->v] == INFINITO) {  // se ainda não foi visitado, atualiza a distância
                dist[n->v] = dist[v] + 1;  
                enfileira(&f, n->v);       // enfileira para continuar a busca

                if (n->v == destino) {     // se encontramos o destino retorna o tamanho da rota
                    free(dist);
                    return dist[n->v];     
                }
            }
        }
    }

    free(dist);
    return -1;  // se não encontrou o destino
}
