#ifndef FILA_H_
#define FILHA_H_

struct fila {
    int tam;
    struct nodo_fila* inicio;
    struct nodo_fila* fim;
};

struct nodo_fila {
    struct nodo* nodo;
    struct nodo_fila* proximo;
};

/* Adiciona novo nodo a fila */
void enfileirar (struct fila* F, struct nodo* nodo);

/* Remove a cabeca da fila */
struct nodo_fila* desenfileirar (struct fila *F);

#endif