#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001
#define LOGN 10

int pai[MAXN][LOGN];
int profundidade[MAXN];
int raiz[MAXN];
int N, M;

void initialize() {
    for (int i = 1; i <= N; i++) {
        raiz[i] = i;
        profundidade[i] = 0;
        for (int j = 0; j < LOGN; j++) {
            pai[i][j] = -1;
        }
    }
}

int acharRaiz(int x) {
    if (raiz[x] == x)
        return x;
    return raiz[x] = acharRaiz(raiz[x]);
}

void link(int A, int B) {
    int raizA = acharRaiz(A);
    int raizB = acharRaiz(B);
    if (raizA != raizB) {
        raiz[raizA] = raizB;
        pai[A][0] = B;
        profundidade[A] = profundidade[B] + 1;
        for (int j = 1; j < LOGN; j++) {
            if (pai[A][j-1] != -1) {
                pai[A][j] = pai[pai[A][j-1]][j-1];
            }
        }
    }
}

void cut(int A) {
    int p = pai[A][0];
    if (p != -1) {
        raiz[A] = A;
        pai[A][0] = -1;
        for (int j = 1; j < LOGN; j++) {
            pai[A][j] = -1;
        }
    }
}

int lca(int A, int B) {
    if (profundidade[A] < profundidade[B]) {
        int temp = A;
        A = B;
        B = temp;
    }

    int diff = profundidade[A] - profundidade[B];
    for (int i = 0; i < LOGN; i++) {
        if ((diff >> i) & 1) {
            A = pai[A][i];
        }
    }

    if (A == B)
        return A;

    for (int i = LOGN - 1; i >= 0; i--) {
        if (pai[A][i] != pai[B][i]) {
            A = pai[A][i];
            B = pai[B][i];
        }
    }

    return pai[A][0];
}

int main() {
    scanf("%d %d", &N, &M);
    initialize();

    char operacao[5];
    int A, B;

    for (int i = 0; i < M; i++) {
        scanf("%s", operacao);
        if (strcmp(operacao, "link") == 0) {
            scanf("%d %d", &A, &B);
            link(A, B);
        } else if (strcmp(operacao, "cut") == 0) {
            scanf("%d", &A);
            cut(A);
        } else if (strcmp(operacao, "lca") == 0) {
            scanf("%d %d", &A, &B);
            printf("%d\n", lca(A, B));
        }
    }

    return 0;
}
