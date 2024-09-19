#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

typedef struct No {
    char caractere;
    int frequencia;
    struct No *esq, *dir;
} No;

typedef struct HeapMin {
    int tamanho;
    int capacidade;
    No** array;
} HeapMin;

No* criarNo(char caractere, int frequencia) {
    No* no = (No*)malloc(sizeof(No));
    no->caractere = caractere;
    no->frequencia = frequencia;
    no->esq = no->dir = NULL;

    return no;
}

HeapMin* criarHeapMin(int capacidade) {
    HeapMin* heapMin = (HeapMin*)malloc(sizeof(HeapMin));
    heapMin->tamanho = 0;
    heapMin->capacidade = capacidade;
    heapMin->array = (No**)malloc(heapMin->capacidade * sizeof(No*));

    return heapMin;
}

void trocarNos(No** a, No** b) {
    No* t = *a;
    *a = *b;
    *b = t;
}

void heapifyMin(HeapMin* heapMin, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < heapMin->tamanho && heapMin->array[esq]->frequencia < heapMin->array[menor]->frequencia)
        menor = esq;

    if (dir < heapMin->tamanho && heapMin->array[dir]->frequencia < heapMin->array[menor]->frequencia)
        menor = dir;

    if (menor != idx) {
        trocarNos(&heapMin->array[menor], &heapMin->array[idx]);
        heapifyMin(heapMin, menor);
    }
}

No* extrairMinimo(HeapMin* heapMin) {
    No* temp = heapMin->array[0];
    heapMin->array[0] = heapMin->array[heapMin->tamanho - 1];
    --heapMin->tamanho;
    
    heapifyMin(heapMin, 0);

    return temp;
}

void inserirHeapMin(HeapMin* heapMin, No* no) {
    ++heapMin->tamanho;
    int i = heapMin->tamanho - 1;

    while (i && no->frequencia < heapMin->array[(i - 1) / 2]->frequencia) {
        heapMin->array[i] = heapMin->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    heapMin->array[i] = no;
}

HeapMin* construirHeapMin(char caracteres[], int frequencias[], int tamanho) {
    HeapMin* heapMin = criarHeapMin(tamanho);
    for (int i = 0; i < tamanho; ++i)
        heapMin->array[i] = criarNo(caracteres[i], frequencias[i]);

    heapMin->tamanho = tamanho;

    for (int i = (heapMin->tamanho - 2) / 2; i >= 0; --i)
        heapifyMin(heapMin, i);

    return heapMin;
}

No* construirArvoreHuffman(char caracteres[], int frequencias[], int tamanho) {
    No *esq, *dir, *topo;
    HeapMin* heapMin = construirHeapMin(caracteres, frequencias, tamanho);

    while (heapMin->tamanho != 1) {
        esq = extrairMinimo(heapMin);
        dir = extrairMinimo(heapMin);

        topo = criarNo('$', esq->frequencia + dir->frequencia);
        topo->esq = esq;
        topo->dir = dir;

        inserirHeapMin(heapMin, topo);
    }

    return extrairMinimo(heapMin);
}

void calcularBits(No* raiz, int arr[], int topo, int* totalBits) {
    if (raiz->esq) {
        arr[topo] = 0;
        calcularBits(raiz->esq, arr, topo + 1, totalBits);
    }
    if (raiz->dir) {
        arr[topo] = 1;
        calcularBits(raiz->dir, arr, topo + 1, totalBits);
    }
    if (!(raiz->esq) && !(raiz->dir)) {
        *totalBits += topo * raiz->frequencia;
    }
}

int obterTotalBitsHuffman(char caracteres[], int frequencias[], int tamanho) {
    No* raiz = construirArvoreHuffman(caracteres, frequencias, tamanho);
    int arr[MAX_CHAR], topo = 0;
    int totalBits = 0;

    calcularBits(raiz, arr, topo, &totalBits);

    return totalBits;
}

int main() {
    char texto[500001];
    char caracteres[MAX_CHAR];
    int contagemFreq = 0;
    int frequencias[MAX_CHAR] = {0};
    int comprimentoTexto = 0;

    while (fgets(texto + comprimentoTexto, sizeof(texto) - comprimentoTexto, stdin) != NULL) {
        comprimentoTexto += strlen(texto + comprimentoTexto);
    }

    for (int i = 0; i < comprimentoTexto; ++i) {
        frequencias[(int)texto[i]]++;
    }

    for (int i = 0; i < MAX_CHAR; ++i) {
        if (frequencias[i] > 0) {
            caracteres[contagemFreq] = (char)i;
            frequencias[contagemFreq] = frequencias[i];
            contagemFreq++;
        }
    }

    int totalBits = obterTotalBitsHuffman(caracteres, frequencias, contagemFreq);

    printf("%d\n", totalBits);

    return 0;
}
