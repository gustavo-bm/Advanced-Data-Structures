#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int linha;
    int coluna;
    int valor;
} Vetor;

int comparar(const void *a, const void *b);
int busca(int i, int j, int A[], int C[], int R[], int numValores, int numIndicesR);

int main(void)
{
    int numValores;

    scanf("%d", &numValores);
    Vetor *v = (Vetor *)malloc(sizeof(Vetor) * numValores);

    for (int i = 0; i < numValores; i++)
    {
        scanf("%d %d %d", &v[i].linha, &v[i].coluna, &v[i].valor);
    }

    // ordena as triplas por linha e coluna
    qsort(v, numValores, sizeof(Vetor), comparar);

    int numLinhas = v[numValores - 1].linha + 1;
    int numIndicesR = numLinhas + 1;

    int *A = (int *)malloc(sizeof(int) * numValores);
    int *C = (int *)malloc(sizeof(int) * numValores);

    for (int i = 0; i < numValores; i++)
    {
        A[i] = v[i].valor;
        C[i] = v[i].coluna;
    }

    // construcao do vetor R
    int *R = (int *)malloc(sizeof(int) * numIndicesR);
    int linhaAtual = -1;
    int contador = 0;

    for (int i = 0; i < numValores; i++)
    {
        if (v[i].linha != linhaAtual)
        {
            while (linhaAtual < v[i].linha)
            {
                R[++linhaAtual] = contador;
            }
        }
        contador++;
    }
    while (++linhaAtual <= numLinhas)
    {
        R[linhaAtual] = contador;
    }

    int i_key, j_key;
    while (1)
    {
        scanf("%d %d", &i_key, &j_key);
        if (i_key == -1 || j_key == -1)
            break;

        int elemento = busca(i_key, j_key, A, C, R, numValores, numIndicesR);

        printf("(%d,%d) = %d\n", i_key, j_key, elemento);
    }

    free(A);
    free(C);
    free(R);

    return 0;
}

// ----------------------------- FUNÇÕES ------------------------------------------------------

// lembrando que o qsort deve retornar um numero negativo se o primeiro elemento for menor que o segundo, 
// um número positivo se o 
// primeiro elemento for maior que o segundo, e zero se os elementos forem iguais.

int comparar(const void *a, const void *b)
{
    Vetor *tripla1 = (Vetor *)a;
    Vetor *tripla2 = (Vetor *)b;

    // primeiro, compara os valores de i
    if (tripla1->linha != tripla2->linha)
    {
        return tripla1->linha - tripla2->linha;
    }

    // se i for igual, compara os valores de j
    return tripla1->coluna - tripla2->coluna;
}

int busca(int i, int j, int A[], int C[], int R[], int numValores, int numIndicesR)
{
    if (i < numIndicesR - 1)
    {
        for (int k = R[i]; k < R[i + 1]; k++)
        {
            if (k < numValores && C[k] == j)
            {
                return A[k];
            }
        }
    }

    return 0;
}