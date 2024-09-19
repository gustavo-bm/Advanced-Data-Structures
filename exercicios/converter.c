#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int V;
    int A;
    int **mat;
} g_matrix;

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

void inicializarM(g_matrix* M, int nVertices) {
    M->V = nVertices;
    M->A = 0;

    M->mat = (int**)malloc(nVertices * sizeof(int*));

    for (int i = 0; i < nVertices; i++)
        M->mat[i] = (int*)malloc(nVertices * sizeof(int));
    
    for (int i = 0; i < nVertices; i++) {
        for (int j = 0; j < nVertices; j++) {
            M->mat[i][j] = 0;
        }
    }      
}

void adicionarM(g_matrix* M, int v, int w) {
    M->mat[v][w] = 1;
    M->A++;
}

void inicializarL(g_list* L, int nVertices) {
    L->V = nVertices;
    L->A = 0;

    L->adj = (link*)malloc(nVertices * sizeof(link));
    
    for (int i = 0; i < nVertices; i++)
        L->adj[i] = NULL;
}

void adicionarL(g_list* L, int v, int w) {
    link n = (link)malloc(sizeof(struct node));
    n->v = w;
    n->next = L->adj[v];
    L->adj[v] = n;
    L->A++;
}

// recebe um grafo representado por matriz de adjacencias e converte na representacao por lista de adjacencias
g_list *matrix2list( g_matrix *m ) {
    g_list* L = (g_list*)malloc(sizeof(g_list));
    
    L->V = m->V;
    L->A = m->A;

    L->adj = (link*)malloc(L->V * sizeof(link));
    for (int i = 0; i < L->V; i++) {
        L->adj[i] = NULL;
    }

    for (int i = 0; i < L->V; i++) {
        for (int i = 0; i < L->V; i++) {
            if (m[i][j] == 1) {
                link n = (link*)malloc(sizeof(struct node));
                n->v = j;
                n->next = L->adj[i];
                L->adj[i] = n;
            }
        }        
    }

    return L;
}

// recebe um grafo representado por lista de adjacencias e converte na representacao por lista de adjacencias
g_matrix *list2matrix( g_list *l ) {
    g_matrix* M = (g_matrix*)malloc(sizeof(g_matrix));
    M->V = l->V;
    M->A = l->A;

    M->mat = (int**)malloc(M->V * sizeof(int*));
    for (int i = 0; i < M->V; i++) {
        M->mat[i] = (int*)malloc(M->V * sizeof(int));
    }

    for (int i = 0; i < M->V; i++) {
        for (int j = 0; j < M->V; j++) {
            M->mat[i][j] = 0;
        }
    }

    for (int i = 0; i < M->V; i++) {
        for (link n = l->adj[i]; n != NULL; n = n->next) {
            M->mat[i][n->v] = 1;
        }
    }

    return M;
}

int main() {

    // criar um grafo representado por matriz de adjacências
    g_matrix *M;

    inicializarM(M, 5);

    adicionarM(M, 0, 1);
    adicionarM(M, 0, 2);
    adicionarM(M, 1, 1);
    adicionarM(M, 1, 2);
    adicionarM(M, 1, 4);
    adicionarM(M, 3, 5);
    adicionarM(M, 2, 3);

    g_list* g = matrix2list(M);
    g_matrix m = list2matrix(g);

    // criar um grafo representado por lista de adjacências
    // g_list *L;
    // inicializarL(L, 5);

    // adicionarL(L, 0, 1);
    // adicionarL(L, 0, 2);
    // adicionarL(L, 1, 1);
    // adicionarL(L, 1, 2);
    // adicionarL(L, 1, 4);
    // adicionarL(L, 3, 5);
    // adicionarL(L, 2, 3);





    return 0
}