#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 52

typedef struct Node {
    char data;
    struct Node *esq;
    struct Node *dir;
} Node;

Node* newNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->esq = node->dir = NULL;
    return node;
}

int search(char vetor[], int inicio, int fim, char valor) {
    for (int i = inicio; i <= fim; i++) {
        if (vetor[i] == valor) {
            return i;
        }
    }
    return -1;
}

Node* gerarArvore(char emOrdem[], char preOrdem[], int emInicio, int emFinal, int* preIndice) {
    if (emInicio > emFinal) {
        return NULL;
    }

    Node* node = newNode(preOrdem[*preIndice]);
    (*preIndice)++;

    // se o nó não tem filhos, retorna o proprio nó
    if (emInicio == emFinal) {
        return node;
    }

    int indice = search(emOrdem, emInicio, emFinal, node->data);

    // usar a posição do indice na sequencia em ordem para dividir a árvore nas suas sub-árvores esquerda e direita
    node->esq = gerarArvore(emOrdem, preOrdem, emInicio, indice - 1, preIndice);
    node->dir = gerarArvore(emOrdem, preOrdem, indice + 1, emFinal, preIndice);

    return node;
}

void printPosOrdem(Node* node) {
    if (node == NULL) {
        return;
    }
    printPosOrdem(node->esq);
    printPosOrdem(node->dir);
    printf("%c", node->data);
}

int main() {
    int C;
    scanf("%d", &C);

    while (C--) {
        int N;
        char preOrdem[MAX_NODES], emOrdem[MAX_NODES];
        scanf("%d %s %s", &N, preOrdem, emOrdem);

        int preIndice = 0;
        Node* root = gerarArvore(emOrdem, preOrdem, 0, N - 1, &preIndice);

        printPosOrdem(root);
        printf("\n");

        free(root);
    }

    return 0;
}