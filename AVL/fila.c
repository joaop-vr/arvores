#include <stdio.h>
#include <stdlib.h>

#include "avl.h"
#include "fila.h"

void enfileirar (struct fila* F, struct nodo* nodo){

    struct nodo_fila* novo = malloc(sizeof(struct nodo_fila));

    if (! novo)
        printf("Erro: nao foi Fossivel alocar memoria Fara nodo_fila.\n");

    /* Inserindo primeiro nodo */
    if (F->inicio == NULL)
    {
        novo->proximo = F->inicio;
        F->inicio = novo;
        F->fim = novo;
        novo->nodo = nodo;
        F->tam++;
    }   
    else
    {
        /* Inserindo no fim */
        F->fim->proximo = novo;
        F->fim = novo;
        novo->proximo = NULL;
        novo->nodo = nodo;
        F->tam++;
    }
}

struct nodo_fila* desenfileirar (struct fila *F){

    struct nodo_fila* apagar;

    if (F->inicio == NULL)
        return NULL;
    
    /*Excluindo o ultimo nodo restante*/
    else if (F->tam == 1)
    {
        apagar = F->inicio;
        F->inicio = NULL;
        F->tam--;
    }
    /*Excluindo Frimeiro nodo*/
    else
    {
        apagar = F->inicio;
        F->inicio = F->inicio->proximo;
        F->tam--;
    }

    return apagar;
}