#include <stdio.h>
#include <stdlib.h>

// Definições fornecidas
typedef struct node *Link;

struct node {
    int v;      // vértice
    Link next;  // próximo nó na lista de adjacência
};

typedef struct {
    int V;   // número de vértices
    int A;   // número de arestas
    Link *adj;  // lista de adjacência (array de links)
} g_list;

// Função auxiliar para realizar a DFS e detectar ciclos
int dfsCycle(g_list *g, int v, int *visitado, int *emProcesso) {
    visitado[v] = 1;   // Marca o vértice como visitado
    emProcesso[v] = 1; // Marca o vértice como em processamento

    // Percorre a lista de adjacência do vértice v
    for (Link n = g->adj[v]; n != NULL; n = n->next) {
        int w = n->v; // vértice adjacente

        // Se o vértice adjacente ainda não foi visitado, realiza DFS
        if (!visitado[w]) {
            if (dfsCycle(g, w, visitado, emProcesso)) {
                return 1; // Ciclo detectado
            }
        }
        // Se o vértice adjacente está em processamento, há um ciclo
        else if (emProcesso[w]) {
            return 1;
        }
    }

    emProcesso[v] = 0; // Marca o vértice como completamente processado
    return 0;          // Não há ciclo
}

// Função principal para verificar se o grafo tem ciclos
int isCyclic(g_list *g) {
    int *visitado = (int *)calloc(g->V, sizeof(int));  // Array para marcar vértices visitados
    int *emProcesso = (int *)calloc(g->V, sizeof(int)); // Array para marcar vértices em processamento

    // Realiza a DFS para cada vértice não visitado
    for (int v = 0; v < g->V; v++) {
        if (!visitado[v]) {
            if (dfsCycle(g, v, visitado, emProcesso)) {
                free(visitado);
                free(emProcesso);
                return 1; // Ciclo encontrado
            }
        }
    }

    free(visitado);
    free(emProcesso);
    return 0; // Nenhum ciclo encontrado
}

int main() {
    // Aqui você pode adicionar a criação do grafo e testar a função isCyclic
    return 0;
}
