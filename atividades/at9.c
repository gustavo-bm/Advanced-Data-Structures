#include <stdio.h>
#include <stdlib.h>

#define MAX 200

typedef struct No {
    int vertice;
    struct No *prox;
} No;

typedef struct {
    No *cabeca;
} ListaAdj;

ListaAdj grafo[MAX];

typedef struct {
    int vertice;
    int d, f;
} VerticeInfo;

void adicionarAresta(int u, int v) {
    No *novoNo = (No*) malloc(sizeof(No));
    novoNo->vertice = v;
    novoNo->prox = grafo[u].cabeca;
    grafo[u].cabeca = novoNo;
}

void dfsVisita(int u, int *status, VerticeInfo *info, int *tempo, int *aciclico) {
    status[u] = 1;
    info[u].d = ++(*tempo);

    No *vizinho = grafo[u].cabeca;

    while (vizinho != NULL) {
        int v = vizinho->vertice;

        if (status[v] == 0) {
            dfsVisita(v, status, info, tempo, aciclico);
        } else if (status[v] == 1) {
            *aciclico = 0;
        }

        vizinho = vizinho->prox;
    }

    status[u] = 2;
    info[u].f = ++(*tempo);
}

void dfs(int n, int *status, VerticeInfo *info, int *aciclico) {
    int tempo = 0;
   
    for (int i = 1; i <= n; i++) {
        status[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        if (status[i] == 0) {
            dfsVisita(i, status, info, &tempo, aciclico);
        }
    }
}

int comparar(const void *a, const void *b) {
    VerticeInfo *v1 = (VerticeInfo *)a;
    VerticeInfo *v2 = (VerticeInfo *)b;

    return v1->d - v2->d;
}

int main() {
    int n, u, v;

    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        grafo[i].cabeca = NULL;
    }
   
    while (1) {
        scanf("%d,%d", &u, &v);
        
        if (u == 0 && v == 0) {
            break;
        }

        adicionarAresta(u, v);
    }
   
    int status[MAX];
    VerticeInfo info[MAX];

    for (int i = 1; i <= n; i++) {
        info[i].vertice = i;
        info[i].d = 0;
        info[i].f = 0;
    }

    int aciclico = 1;
   
    dfs(n, status, info, &aciclico);

    qsort(info + 1, n, sizeof(VerticeInfo), comparar);

    for (int i = 1; i <= n; i++) {
        printf("%d [%d,%d]\n", info[i].vertice, info[i].d, info[i].f);
    }
   
    if (aciclico) {
        printf("aciclico: sim\n");
    } else {
        printf("aciclico: nao\n");
    }

    return  0;
}
