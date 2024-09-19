#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node {
    int v;
    link next;
};

typedef struct {
    int V;
    int A;
    link *adj;
} g_list;

void inicializarL(g_list *L, int nVertices) {
    L->V = nVertices;
    L->A = 0;

    L->adj = (link *)malloc(nVertices * sizeof(link));

    for (int i = 0; i < nVertices; i++)
        L->adj[i] = NULL;
}

void adicionarL(g_list *L, int v, int w) {
    link n = (link)malloc(sizeof(struct node));
    n->v = w;
    n->next = L->adj[v];
    L->adj[v] = n;
    L->A++;
}

int dfs(g_list *g, int v, int *cores, int corAtual) {
    cores[v] = corAtual;

    for (link n = g->adj[i]; n != NULL; n = n->next) {
        if (cores[n->v] != -1) {
            if (!dfs(g, n->v, cores, 1 - corAtual)) {
                return 0;
            }
        } else if (cores[n->v] == cores[v]) {
            return 0;
        }
    }

    return 1;
}

int bipartido(g_list *g) {
    int *cores = (int *)malloc(g->V * sizeof(int));

    for (int i = 0; i < g->V; i++) {
        cores[i] = -1; // não visitado
    }

    for (int i = 0; i < g->V; i++) {
        if (cores[i] == -1) {
            if (!dfs(g, v, cores, 0)) {
                free(cores);
                return 0;
            }
        }
    }

    free(cores);
    return true;
}

int main() {

    // criar um grafo representado por lista de adjacências
    g_list *L;
    inicializarL(L, 5);

    adicionarL(L, 0, 1);
    adicionarL(L, 0, 2);
    adicionarL(L, 1, 1);
    adicionarL(L, 1, 2);
    adicionarL(L, 1, 4);
    adicionarL(L, 3, 5);
    adicionarL(L, 2, 3);

    return 0
}