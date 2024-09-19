#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct node_ {
	int data;
	struct node_ *dir, *esq;
} node;

node* inserir(node* p, int dados) {
    if (p == NULL) {
        node* novo = (node*)malloc(sizeof(node));
        novo->data = dados;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (dados < p->data) {
        p->esq = inserir(p->esq, dados);
	}
    else {
        p->dir = inserir(p->dir, dados);
	}
    return p;
}


void destruir(node *p) {
    if (p != NULL) {
        destruir(p->esq);
        destruir(p->dir);
        free(p);
    }
}

void pos_order(node *p, void (*process)(int dado)) {
    if (p != NULL) {
        pos_order(p->esq, process);
        pos_order(p->dir, process);
        process(p->data);
    }
}

void pre_order(node *p, void (*process)(int dado)) {
    if (p != NULL) {
        process(p->data);
        pre_order(p->esq, process);
        pre_order(p->dir, process);
    }
}

void in_order(node *p, void (*process)(int dado)) {
    if (p != NULL) {
        in_order(p->esq, process);
        process(p->data);
        in_order(p->dir, process);
    }
}


void in_level(node *p, void (*process)(int dado)) {
    queue q;

    initialize(&q);
    if (p != NULL) {
        push(&q, p);
        while (!empty(&q)) {
            node* atual = (node*)front(&q);
            pop(&q);
            process(atual->data);
            if (atual->esq != NULL) push(&q, atual->esq);
            if (atual->dir != NULL) push(&q, atual->dir);
        }
    }
    destroy(&q);
}


void print(int dado) {
	printf(" %d", dado);
}

int main() {

	int n,a;
	scanf("%d", &n);
	
	node* raiz = 0;
	
	for(int i=0;i<n; i++) {
		scanf("%d", &a);
		raiz = inserir(raiz,a);
	}
	
	printf("Pr.:");
	pre_order(raiz, print);
	printf("\n");
	printf("In.:");
	in_order(raiz, print);
	printf("\n");
	printf("Po.:");
	pos_order(raiz, print);
	printf("\n");
	printf("Ni.:");
	in_level(raiz, print);
	printf("\n");
	
	destruir(raiz);
	
	return 0;
}
