#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _bst {
    struct _bst* l;
    struct _bst* r;
    char* str;
} bst;

bst* get(bst* root, char* str) {
    while (root != NULL) {
        int cmp = strcmp(root->str, str);
        if (cmp == 0)
            return root;
        else if (cmp > 0)
            root = root->l;
        else
            root = root->r;
    }
    
    return NULL;
}

bst* put(bst* root, char* str) {
    if(root) {
        int cmp = strcmp(root->str, str);
        if(cmp > 0)
            root->l = put(root->l, str);
        else if (cmp < 0)
            root->r = put(root->r, str);
        return root;
    } else {
        bst* novo = (bst*)malloc(sizeof(bst));
        novo->str = (char*)malloc(sizeof(char)*(strlen(str)+1));
        strcpy(novo->str, str);
        novo->l = novo->r = NULL;
        return novo;
    }
}

bst* max(bst* root) {
    while (root->r != NULL) {
        root = root->r;
    }

    return root;
}

bst* min(bst* root) {
    while (root->l != NULL) {
        root = root->l;
    }

    return root;
}

bst* rem(bst* root, char* str) {
    if (root == NULL) return NULL;

    int cmp = strcmp(root->str, str);
    if (cmp > 0) {
        root->l = rem(root->l, str);
    } else if (cmp < 0) {
        root->r = rem(root->r, str);
    } else {
        if (root->l == NULL) {
            bst* temp = root->r;
            free(root->str);
            free(root);
            return temp;
        } else if (root->r == NULL) {
            bst* temp = root->l;
            free(root->str);
            free(root);
            return temp;
        }
        
        bst* temp = min(root->r);
        char* tempStr = root->str;
        root->str = temp->str;
        temp->str = tempStr;
        root->r = rem(root->r, temp->str);
    }

    return root;
}

void del(bst* root) {
    if(root) {
        del(root->l);
        del(root->r);
        free(root->str);
        free(root);
    }
}

int main() {
    char comando[2], palavra[255];
    bst* raiz = NULL;

    while(scanf("%s", comando) != EOF) {
        scanf("%s", palavra);
        if(comando[0] == 'P') 
            raiz = put(raiz, palavra);
        else if(comando[0] == 'R') 
            raiz = rem(raiz, palavra);
        else if(comando[0] == 'G') {
            bst* result = get(raiz, palavra);
            if(result)
                printf("%s encontrada\n", result->str);
            else
                printf("%s nao foi encontrada\n", palavra);
        }
    }

    del(raiz);

    return 0;
}
