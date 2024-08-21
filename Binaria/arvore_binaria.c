#include <stdio.h>
#include <stdlib.h>

struct nodo {
    char chave[11];
    int valor;
    struct nodo* fe;
    struct nodo* fd;
};

struct arvore {
    size_t qntd_nodos;
    size_t altura;
    struct nodo* raiz;

};

void Percorrer_preOrdem (struct arvore* Tree, struct nodo* aux ) {

    if (aux == NULL)
        return;
    
    printf("%i ", aux->valor);
    Percorrer_preOrdem(Tree, aux->fe);
    Percorrer_preOrdem(Tree, aux->fd);

    return;    
}

void Percorrer_emOrdem (struct arvore* Tree, struct nodo* aux ) {

    if (aux == NULL)
        return;
    
    Percorrer_emOrdem(Tree, aux->fe);
    printf("%i ", aux->valor);
    Percorrer_emOrdem(Tree, aux->fd);

    return;    
}

void Percorrer_posOrdem (struct arvore* Tree, struct nodo* aux ) {

    if (aux == NULL)
        return;
    
    Percorrer_posOrdem(Tree, aux->fe);
    Percorrer_posOrdem(Tree, aux->fd);
    printf("%i ", aux->valor);

    return;    
}

struct nodo* Inserir_fila (struct nodo* novo, struct nodo* raiz) {
    
    /*Inserindo o primeiro nodo na arvore (raiz)*/
    printf("\n0\n");
    if (raiz == NULL) {
        printf("\n1\n");
        struct nodo* aux = malloc(sizeof(struct nodo));
        aux = novo;
        aux->fe = NULL;
        aux->fd = NULL;
        printf("CPF do pai: %s", aux->chave);
        return aux;
    }
    else {
        //printf("novo->chave: %s")
        if (novo->valor < raiz->valor)
            raiz->fe = Inserir_fila(novo, raiz->fe);
        else
            raiz->fd = Inserir_fila(novo, raiz->fd); 
        return raiz;
    }   
}

void Adicionar (struct nodo* novo, struct arvore* Tree) {

    printf("===========================================\n");
    printf("Preencha os campos abaixo: \n");

    printf("CPF: ");
    scanf("%s", novo->chave);
    printf("checagem chave: %s\n", novo->chave);

    printf("Valor: ");
    scanf("%i", &novo->valor);
    printf("checagem valor: %i\n", novo->valor);

    Tree->raiz = Inserir_fila(novo, Tree->raiz);
    Tree->qntd_nodos =+ 1;
    printf("Nodo criado e inserido na arvore com sucesso!\n");
}

int calcularAltura(struct nodo* nodo) {
    int altEsq, altDir;
    if (nodo == NULL)
        return-1;
    altEsq= calcularAltura(nodo->fe);
    altDir= calcularAltura(nodo->fd);
    if (altEsq > altDir)
        return altEsq+1;
    else
        return altDir+1;
}

int main () {

    struct arvore* Tree = malloc(sizeof(struct arvore));
    Tree->altura = 0;
    Tree->raiz = NULL;
    int procedimento = 0;

    while (procedimento != 4) {
        printf("===========================================\n");
        printf("Informe o codigo do procedimento que deseja realizar:\n\n");
        printf("1 - Inserir\n");
        printf("2 - Percorrer arvore\n");
        printf("3 - Calcular Altura\n");
        printf("4 - Finalizar\n");
        printf("\nProcesso: ");
        scanf("%i", &procedimento);

        switch (procedimento) {

            /*Case para primeira passagem*/
            case 0:
                break;            
            case 1: {
                int insercoes = 0;
                printf("===========================================\n");
                printf("Qual será o numero de insercoes?");
                scanf("%i", &insercoes);
                for (int i = 0; i < insercoes; i++) {
                    struct nodo* novo = malloc(sizeof(struct nodo));
                    novo->fd = NULL;
                    novo->fe = NULL;
                    Adicionar(novo, Tree);
                }
                printf("\nDados inseridos com sucesso\n\n");
                break;}
            case 2: 
                printf("===========================================\n");
                printf("Pré-Ordem: ");
                struct nodo* aux = Tree->raiz;
                Percorrer_preOrdem(Tree, aux);
                printf("\n");
                aux = Tree->raiz;
                printf("Em-Ordem: ");
                Percorrer_emOrdem(Tree, aux);
                printf("\n");
                aux = Tree->raiz;
                printf("Pos-Ordem: ");
                Percorrer_posOrdem(Tree, aux);
                printf("\n");
                break;
            case 3:
                printf("===========================================\n");
                int altura = calcularAltura(Tree->raiz);
                if (altura == -1)
                    printf("Altura: 0\n");
                else
                    printf("Altura: %i\n", altura);
                break;
                case 4:
                break;
            default:
                printf("Erro: codigo invalido!\n");
                break;
        }
        //system("cls");
    }

    printf("Sistema: finalizando...\n");
    return 0;
}