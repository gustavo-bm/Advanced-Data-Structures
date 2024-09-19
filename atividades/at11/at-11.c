#include <stdio.h>
#include <stdlib.h>
#include "filaPrioridade.h"

typedef struct No {
    int vertice;
    struct No *prox;
} No;

typedef struct Lista {
    No *inicio;
} Lista;

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int *grauEntrada = (int *)calloc(N, sizeof(int));
    Lista *adj = (Lista *)malloc(N * sizeof(Lista)); // lista de adjacências
    
    // inicializando as listas de adjacencia vazias
    for (int i = 0; i < N; i++) {
        adj[i].inicio = NULL;
    }

    // colocando na lista de adjacência
    for (int i = 0; i < M; i++) {
        int A, B;
        scanf("%d %d", &A, &B);
        
        // adiciona B na lista de adjacencia de A
        No *novoNo = (No *)malloc(sizeof(No));
        novoNo->vertice = B;
        novoNo->prox = adj[A].inicio;
        adj[A].inicio = novoNo;

        grauEntrada[B]++;  // Incrementa o grau de entrada de B
    }

    FilaPrioridade heap;
    inicializarFila(&heap, N);

    // adiciona todas as tarefas com grau de entrada 0 na fila (Kahn)
    for (int i = 0; i < N; i++) {
        if (grauEntrada[i] == 0) {
            inserirFila(&heap, i);
        }
    }

    int cont = 0;
    int *result = (int *)malloc(N * sizeof(int));

    while (!vazia(&heap)) {
        int u = retirarFila(&heap);
        result[cont++] = u;

        // Processa todos os nós adjacentes de u
        No *atual = adj[u].inicio;
        while (atual != NULL) {
            int v = atual->vertice;
            grauEntrada[v]--;

            if (grauEntrada[v] == 0) {
                inserirFila(&heap, v);
            }

            atual = atual->prox;
        }
    }

    if (cont != N) {
        printf("*\n");  // ciclo de dependencia
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d\n", result[i]);
        }
    }

    for (int i = 0; i < N; i++) {
        No *atual = adj[i].inicio;
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(adj);
    free(grauEntrada);
    free(result);
    liberar(&heap);

    return 0;
}
