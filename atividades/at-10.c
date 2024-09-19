#include <stdio.h>
#include <stdlib.h>

#define MAX 200

typedef struct {
    int V;
    int **adj;
} Graph;

typedef struct {
    int items[MAX];
    int front, rear;
} Fila;

void inicializarF(Fila* f) {
    f->front = -1;
    f->rear = -1;
}

int vaziaF(Fila* f) {
    return f->front == -1;
}

void insereF(Fila* f, int elemento) {
    if (f->rear == MAX - 1) {
        printf("Fila cheia!\n");
        return;
    }

    if (f->front == -1)
        f->front = 0;

    f->rear++;
    f->items[f->rear] = elemento;
}

int removeF(Fila* f) {
    if (vaziaF(f)) {
        printf("Fila vazia!\n");
        return -1;
    }

    int elemento = f->items[f->front];
    if (f->front >= f->rear) {
        f->front = -1;
        f->rear = -1;
    } else {
        f->front++;
    }

    return elemento;
}

void inicializar(Graph* G, int nVertices) {
    G->V = nVertices;

    G->adj = (int**)malloc((nVertices + 1) * sizeof(int*));
    for (int v = 1; v <= nVertices; v++) {
        G->adj[v] = (int*)malloc((nVertices + 1) * sizeof(int));
        for (int w = 1; w <= nVertices; w++) {
            G->adj[v][w] = 0;
        }
    }
}

void adiciona_aresta(Graph* G, int v, int dest) {
    if (G->adj[v][dest] == 0) {
        G->adj[v][dest] = 1;
        G->adj[dest][v] = 1;
    }
}

void bfs(Graph* G, int primeiro) {
    int dist[G->V + 1];
    for (int v = 1; v <= G->V; v++)
        dist[v] = -1;

    Fila f;
    inicializarF(&f);
    insereF(&f, primeiro);
    
    dist[primeiro] = 0;

    while (!vaziaF(&f)) {
        int v = removeF(&f);

        for (int w = 1; w <= G->V; w++) {
            if (G->adj[v][w] == 1 && dist[w] == -1) {
                dist[w] = dist[v] + 1;
                insereF(&f, w);
            }
        }
    }

    printf("Origem da busca: %d\n", primeiro);
    printf("Vertices alcancados e distancias:\n");

    for (int d = 0; d <= G->V; d++) {
        for (int v = 1; v <= G->V; v++) {
            if (dist[v] == d)
                printf("%d %d\n", v, dist[v]);
        }
    }
}

int main() {
    int i, j, primeiro;
    Graph G;

    scanf("%d", &G.V);
    inicializar(&G, G.V);

    do {
        scanf("%d,%d", &i, &j);
        if (i != 0 && j != 0) {
            adiciona_aresta(&G, i, j);
        }
    } while (i != 0 || j != 0);

    scanf("%d", &primeiro);

    bfs(&G, primeiro);
    return 0;
}
