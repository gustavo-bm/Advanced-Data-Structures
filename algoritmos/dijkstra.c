#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define V 9 // Número de vértices no grafo

// Um nó na fila de prioridade
struct NoFila {
    int vertice;
    int distancia;
};

// Uma estrutura para representar a fila de prioridade
struct FilaPrioridade {
    int tamanho;
    int capacidade;
    int *pos; // Posição de cada vértice na fila de prioridade
    struct NoFila **array;
};

// Função para criar um novo nó da fila de prioridade
struct NoFila* novoNoFila(int vertice, int distancia) {
    struct NoFila* no = (struct NoFila*) malloc(sizeof(struct NoFila));
    no->vertice = vertice;
    no->distancia = distancia;
    return no;
}

// Função para criar uma fila de prioridade
struct FilaPrioridade* criarFilaPrioridade(int capacidade) {
    struct FilaPrioridade* fila = (struct FilaPrioridade*) malloc(sizeof(struct FilaPrioridade));
    fila->pos = (int *) malloc(capacidade * sizeof(int));
    fila->tamanho = 0;
    fila->capacidade = capacidade;
    fila->array = (struct NoFila**) malloc(capacidade * sizeof(struct NoFila*));
    return fila;
}

// Função para trocar dois nós da fila de prioridade
void trocarNo(struct NoFila** a, struct NoFila** b) {
    struct NoFila* temp = *a;
    *a = *b;
    *b = temp;
}

// Função para ajustar a fila de prioridade (min-heapify)
void minHeapify(struct FilaPrioridade* fila, int idx) {
    int menor = idx;
    int esquerda = 2 * idx + 1;
    int direita = 2 * idx + 2;

    if (esquerda < fila->tamanho && fila->array[esquerda]->distancia < fila->array[menor]->distancia)
        menor = esquerda;

    if (direita < fila->tamanho && fila->array[direita]->distancia < fila->array[menor]->distancia)
        menor = direita;

    if (menor != idx) {
        // Os nós trocados também precisam atualizar suas posições na fila
        struct NoFila* menorNo = fila->array[menor];
        struct NoFila* idxNo = fila->array[idx];

        // Trocar posições
        fila->pos[menorNo->vertice] = idx;
        fila->pos[idxNo->vertice] = menor;

        // Trocar nós
        trocarNo(&fila->array[menor], &fila->array[idx]);

        minHeapify(fila, menor);
    }
}

// Função para verificar se a fila de prioridade está vazia
int filaVazia(struct FilaPrioridade* fila) {
    return fila->tamanho == 0;
}

// Função para extrair o nó com a menor distância (a raiz da fila de prioridade)
struct NoFila* extrairMinimo(struct FilaPrioridade* fila) {
    if (filaVazia(fila))
        return NULL;

    // A raiz do heap é o nó com a menor distância
    struct NoFila* raiz = fila->array[0];

    // Substituir a raiz pelo último nó e reduzir o tamanho da fila
    struct NoFila* ultimoNo = fila->array[fila->tamanho - 1];
    fila->array[0] = ultimoNo;

    // Atualizar a posição do último nó
    fila->pos[raiz->vertice] = fila->tamanho - 1;
    fila->pos[ultimoNo->vertice] = 0;

    // Reduzir o tamanho da fila e ajustar o heap
    fila->tamanho--;
    minHeapify(fila, 0);

    return raiz;
}

// Função para reduzir a distância de um vértice e ajustar a fila
void diminuirDistancia(struct FilaPrioridade* fila, int vertice, int distancia) {
    // Encontrar o índice do vértice e atualizar sua distância
    int i = fila->pos[vertice];
    fila->array[i]->distancia = distancia;

    // Ajustar a fila para garantir a propriedade do min-heap
    while (i && fila->array[i]->distancia < fila->array[(i - 1) / 2]->distancia) {
        // Trocar o nó com seu pai
        fila->pos[fila->array[i]->vertice] = (i - 1) / 2;
        fila->pos[fila->array[(i - 1) / 2]->vertice] = i;
        trocarNo(&fila->array[i], &fila->array[(i - 1) / 2]);

        // Ir para o próximo nível
        i = (i - 1) / 2;
    }
}

// Função para verificar se um vértice está na fila de prioridade
bool estaNaFila(struct FilaPrioridade *fila, int vertice) {
    if (fila->pos[vertice] < fila->tamanho)
        return true;
    return false;
}

// Função para imprimir a solução
void imprimirSolucao(int distancias[], int n) {
    printf("Vértice \t Distância da Origem\n");
    for (int i = 0; i < n; i++)
        printf("%d \t\t %d\n", i, distancias[i]);
}

// Implementação do algoritmo de Dijkstra usando fila de prioridade
void dijkstra(int grafo[V][V], int origem) {
    // Array que armazena as menores distâncias de cada vértice
    int distancias[V];

    // Fila de prioridade
    struct FilaPrioridade* fila = criarFilaPrioridade(V);

    // Inicializa todas as distâncias como INFINITO e insere todos os vértices na fila
    for (int v = 0; v < V; v++) {
        distancias[v] = INT_MAX;
        fila->array[v] = novoNoFila(v, distancias[v]);
        fila->pos[v] = v;
    }

    // A distância da origem para ela mesma é 0
    distancias[origem] = 0;
    diminuirDistancia(fila, origem, distancias[origem]);

    fila->tamanho = V;

    // Loop principal para processar todos os vértices
    while (!filaVazia(fila)) {
        // Extrai o vértice com a menor distância
        struct NoFila* noMinimo = extrairMinimo(fila);
        int u = noMinimo->vertice;

        // Atualiza as distâncias dos vértices adjacentes
        for (int v = 0; v < V; v++) {
            // Apenas processa os vértices adjacentes a u
            if (grafo[u][v] && estaNaFila(fila, v) && distancias[u] != INT_MAX && distancias[u] + grafo[u][v] < distancias[v]) {
                distancias[v] = distancias[u] + grafo[u][v];
                diminuirDistancia(fila, v, distancias[v]);
            }
        }
    }

    // Imprime a solução final
    imprimirSolucao(distancias, V);
}

int main() {
    // Um exemplo de grafo representado por uma matriz de adjacências
    int grafo[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    dijkstra(grafo, 0);

    return 0;
}
