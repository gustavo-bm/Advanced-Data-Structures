#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    unsigned dest;
    struct node *prox;
} Node;

typedef struct graph {
    unsigned V;
    int A;
    Node **adj;
} Graph;

typedef struct {
    int vertice;
    int descoberta;
    int finalizacao;
} Timestamp;

void inicializar(Graph *G, unsigned nvertices) {
    G->V = nvertices;
    G->A = 0;
    G->adj = (Node**)malloc(sizeof(Node*) * (G->V + 1));

    for (unsigned v = 1; v <= G->V; v++)
        G->adj[v] = NULL;
}

void adiciona_arco(Graph *G, unsigned v, unsigned dest) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->dest = dest;
    novo->prox = G->adj[v];
    G->adj[v] = novo;
    G->A++;
}

int dfs_private(Graph *G, int vis[], Timestamp ts[], int *tempo, unsigned v) {
    vis[v] = 1;
    ts[v].descoberta = ++(*tempo);

    for (Node* n = G->adj[v]; n != NULL; n = n->prox) {
        if (vis[n->dest] == 0) {
            if (!dfs_private(G, vis, ts, tempo, n->dest))
                return 0;
        } else if (ts[n->dest].finalizacao == 0) {
            return 0;
        }
    }

    ts[v].finalizacao = ++(*tempo);
    return 1;
}

int compara_timestamps(const void *a, const void *b) {
    Timestamp *t1 = (Timestamp *)a;
    Timestamp *t2 = (Timestamp *)b;
    return t1->descoberta - t2->descoberta;
}

void dfs(Graph *G) {
    int *visitado = (int*)malloc(sizeof(int) * (G->V + 1));
    Timestamp *timestamps = (Timestamp*)malloc(sizeof(Timestamp) * (G->V + 1));
    int tempo = 0;
    int aciclico = 1;

    for (unsigned v = 1; v <= G->V; v++) {
        visitado[v] = 0;
        timestamps[v].vertice = v;
        timestamps[v].descoberta = 0;
        timestamps[v].finalizacao = 0;
    }

    for (unsigned v = 1; v <= G->V; v++) {
        if (visitado[v] == 0) {
            if (!dfs_private(G, visitado, timestamps, &tempo, v)) {
                aciclico = 0;
            }
        }
    }

    qsort(timestamps + 1, G->V, sizeof(Timestamp), compara_timestamps);

    for (unsigned v = 1; v <= G->V; v++) {
        printf("%d [%d,%d]\n", timestamps[v].vertice, timestamps[v].descoberta, timestamps[v].finalizacao);
    }

    printf("aciclico: %s\n", aciclico ? "sim" : "nao");

    free(visitado);
    free(timestamps);
}

void liberar_grafo(Graph *G) {
    for (unsigned v = 1; v <= G->V; v++) {
        Node* atual = G->adj[v];
        while (atual != NULL) {
            Node* prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }
    free(G->adj);
    free(G);
}

int main() {
    int i, j;
    Graph *G = (Graph*)malloc(sizeof(Graph));

    scanf("%d", &G->V);

    inicializar(G, G->V);

    do {
        scanf("%d,%d", &i, &j);
        if (i != 0 && j != 0) {
            adiciona_arco(G, i, j);
        }
    } while (i != 0 || j != 0);
    
    dfs(G);
    liberar_grafo(G);

    return 0;
}
