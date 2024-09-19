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

int isEqual( g_list *l , g_matrix *m ) {
    for (int i = 0; i < l->V; i++) {
        for (link n = l->adj[i]; n != NULL; n = n->next) {
            if (m->mat[i][n->v] == 0) {
                return 0;
            }
        }

        for (int j = 0; j < l->V; j++) {
            if (m->mat[i][j] == 1) {
                int igual = 0;
                link temp = l->adj[i];

                while (temp != NULL) {
                    if (j == temp->v) {
                        igual = 1;
                        break;
                    } 
                    temp = temp->next;
                }

                if (!igual) {
                    return 0;
                }
            }
        
        }
    }

    return 1;
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

    criar um grafo representado por lista de adjacências
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