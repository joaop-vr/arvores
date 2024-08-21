#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "avl.h"
#include "fila.h"

//substitua por seus dados
struct aluno* getAluno1(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        exit(1);
    retorno->nome = malloc(sizeof("Joao Pedro Vicente Ramalho"));//sizeof conta o \0
	if(!retorno->nome)
		exit(1);
    retorno->nomeDinf = malloc(sizeof("jpvr22"));
    if(!retorno->nomeDinf){
        exit(1);}
    
	strcpy(retorno->nome, "Joao Pedro Vicente Ramalho");
    strcpy(retorno->nomeDinf, "jpvr22");
    retorno->grr = 20224169;

	return retorno;
}

struct aluno* getAluno2(){
    return NULL;
}

void imprimirDadosAlunos(){
    struct aluno* aluno = getAluno1();
    
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    aluno = getAluno2();
    if(!aluno)
        return;
    
    printf("...E... \n\n");
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);
}

struct nodo* inserir(struct nodo** raiz, int chave){

    struct nodo* outputInserir;

    struct nodo* novo = malloc(sizeof(struct nodo));
    if (! novo)
    {
        printf("Nao foi possivel alocar memoria para o nodo.\n");
        return NULL;
    }

    /*Inserindo uma folha (ou raiz)*/
    if (*raiz == NULL)
    {
        novo->chave = chave;
        novo->fe = NULL;
        novo->fd = NULL;
        novo->pai = NULL;
        novo->balanco = 0;
        novo->alturadoNodo = 0;
        *raiz = novo;
        return *raiz;
    }
    else
    {
        /* Chave ja existe */
        if ((*raiz)->chave == chave)
        {
            printf("Falha ao inserir.\n");
            return NULL;
        }
        else if (chave < (*raiz)->chave)
        {
            if ((outputInserir = inserir(&((*raiz)->fe), chave)) != NULL)
            {
                (*raiz)->fe = outputInserir;
                outputInserir->pai = (*raiz);
            }
        }
        else
        {
            if ((outputInserir = inserir(&((*raiz)->fd), chave)) != NULL)
            {
                (*raiz)->fd = outputInserir;
                outputInserir->pai = (*raiz);
            }
        }

        /* Evitando que nodo de chave repetida entre nessa funcao*/
        if (outputInserir != NULL) 
            atualizarBalanco(outputInserir);

        return *raiz;
    }
}

struct nodo* buscaAntecessor(struct nodo* x){

    struct nodo* aux;

    aux = x->fe;

    while (aux->fd != NULL)
        aux = aux->fd;

    return aux;
}

void transplantar(struct nodo* raiz, struct nodo* A, struct nodo* B){
    
    if (A->pai == NULL)  //caso de A ser raiz
        raiz = B;
    else
    {
        if (A->pai->fe == A) //verificando se A eh filho esquerdo
            A->pai->fe = B;
        else 
            A->pai->fd = B;
    }

    if (B != NULL)
        B->pai = A->pai;

}

int excluir(struct nodo** raiz, int chave){

    struct nodo* antecessor;
    struct nodo* excluirNodo;
    struct nodo* aux;

    excluirNodo = buscar((*raiz), chave);

    if (excluirNodo != NULL)
    {
        if ((excluirNodo->fe == NULL) && (excluirNodo->fd != NULL)) //caso que so tem fd
        {
            transplantar((*raiz), excluirNodo, excluirNodo->fd);
            aux = excluirNodo->fd;
            while (aux->pai != NULL)
            {
                atualizarBalanco(aux);
                aux = aux->pai;
            }
            excluirNodo = NULL;
            free(excluirNodo);
            return 1;
        }
        if ((excluirNodo->fe != NULL) && (excluirNodo->fd == NULL)) //caso que so tem fe
        {
            transplantar((*raiz), excluirNodo, excluirNodo->fe);
            aux = excluirNodo->fe;
            while (aux->pai != NULL)
            {
                atualizarBalanco(aux);
                aux = aux->pai;
            }
            excluirNodo = NULL;
            free(excluirNodo);
            return 1;
        }
        if ((excluirNodo->fe == NULL) && (excluirNodo->fd == NULL)) //caso que nao tem filho
        {
            if (excluirNodo->pai->fe == excluirNodo)
            {
                excluirNodo->pai->fe = NULL;
                aux = excluirNodo->pai;
                while (aux->pai != NULL)
                {
                    atualizarBalanco(aux);
                    aux = aux->pai;
                }
            }
            else
            {
                excluirNodo->pai->fd = NULL;
                aux = excluirNodo->pai;
                    while (aux->pai != NULL)
                    {
                        atualizarBalanco(aux);
                        aux = aux->pai;
                    }
            }
            excluirNodo = NULL;
            free(excluirNodo);
            return 1;
        }

        //caso em que possui ambos os filhos

        antecessor = buscaAntecessor(excluirNodo);

        if (antecessor != excluirNodo->fe)
        {
            transplantar((*raiz), antecessor, antecessor->fe);
            antecessor->fe = excluirNodo->fe;
            antecessor->fe->pai = antecessor;
        }
        transplantar((*raiz), excluirNodo, antecessor);
        antecessor->fd = excluirNodo->fd;
        antecessor->fd->pai = antecessor;


        (*raiz) = antecessor;   //atualizando o ponteiro da raiz
        atualizarBalanco(*raiz);
        atualizarBalanco((*raiz)->fe); // era o pai do antecessor, logo precisa atualizarBalanco
        
        imprimirEmLargura(antecessor);
        
        excluirNodo = NULL;
        free(excluirNodo);
        return 1;
    }

	return 0;
}

struct nodo* buscar(struct nodo* nodo, int chave){

    /* recebe resultado das chamadas recurssivas */
    struct nodo* retorno;

    if(nodo == NULL)
        return NULL;
 
    if(nodo->chave == chave)
        return nodo;

    retorno = buscar(nodo->fe, chave);
    if(retorno)
        return retorno;
    retorno = buscar(nodo->fd, chave);
        return retorno;
}

void imprimirEmOrdem(struct nodo* raiz){
	
    if (raiz == NULL)
        return;
    
    imprimirEmOrdem(raiz->fe);
    printf("%i ", raiz->chave);
    imprimirEmOrdem(raiz->fd);
}

int alturaNodo(struct nodo* aux){

    int cont = 0;

    while (aux->pai != NULL)
    {
        aux = aux->pai;
        cont++;
    }

    return cont;
}

void imprimirEmLargura(struct nodo* raiz){

    /* struct auxiliar para enfileirar/desenfileirar */
    struct nodo_fila* aux;

    /* Contador da altura da arvore */
    int alturaAtual;

    /* Variavel auxilar que recebe a resposta da funcao alturaNodo*/
    int auxAltura;

    /* Inicializando fila */
    struct fila* F = malloc(sizeof(struct fila));
    F->tam = 0;
    F->inicio = NULL;

    alturaAtual = 0;

    enfileirar(F, raiz);

    printf("[0]");

    while ((aux = desenfileirar(F)) != NULL)
    {
        
        /* calcula a altura do nodo para saber se entrou em uma nova altura de nodos,
        se sim printa [%i], onde %i é a altura atual */
        auxAltura = alturaNodo(aux->nodo);
        if (alturaAtual != auxAltura)
        {
            alturaAtual = auxAltura;
            printf("\n[%i]", alturaAtual);
        }

        printf(" %2i(%i)", aux->nodo->chave, aux->nodo->balanco);

        /* verifica se há fe, se sim ele é enfileirado */
        if ((aux->nodo->fe) != NULL)
            enfileirar(F, aux->nodo->fe);

        /* verifica se há fd, se sim ele é enfileirado */
        if ((aux->nodo->fd) != NULL)
            enfileirar(F, aux->nodo->fd);

    }

    printf("\n");
}

int alturaSubarvore(struct nodo* nodo){

    int altEsq, altDir;
    if (nodo == NULL)
        return-1;
    altEsq= alturaSubarvore(nodo->fe);
    altDir= alturaSubarvore(nodo->fd);
    if (altEsq > altDir)
        return altEsq+1;
    else
        return altDir+1;

}

void atualizarBalanco(struct nodo* nodo){

    /* Receberá o nodo "naoBalanceado" após o balanceamento, se necessário */
    struct nodo* nodoBalanceado;

    /* Atualizando o balanco */
    nodo->balanco = alturaSubarvore(nodo->fd) - alturaSubarvore(nodo->fe); //(Altura subárvore Dir) - (Altura subárvore Esq)
        
    /* Verificando se o nodo nao esta balanceado */
    if (!(-1 <= nodo->balanco && nodo->balanco <= 1))
    {

        /* Atualizando o ponteiro para o nodo, apos seu balanceamento*/
        nodoBalanceado = balancear(nodo);

        /* Atualizando o coeficiente de balanceamento dos nodos */
        nodoBalanceado->balanco = alturaSubarvore(nodoBalanceado->fd) - alturaSubarvore(nodoBalanceado->fe);
        nodo->balanco = alturaSubarvore(nodo->fd) - alturaSubarvore(nodo->fe);

    }

}

struct nodo* atualizarRaiz(struct nodo* raiz){

    struct nodo* novaRaiz;    

    /* Atualizando o balanco */
    raiz->balanco = alturaSubarvore(raiz->fd) - alturaSubarvore(raiz->fe); //(Altura subárvore Dir) - (Altura subárvore Esq)
        
    /* Verificando se o nodo nao esta balanceado */
    if (!(-1 <= raiz->balanco && raiz->balanco <= 1))
    {

        /* Atualizando o ponteiro para a novaRaiz, apos o balanceamento*/
        novaRaiz = balancear(raiz);

        /* Atualizando o coeficiente de balanceamento dos nodos */
        novaRaiz->balanco = alturaSubarvore(novaRaiz->fd) - alturaSubarvore(novaRaiz->fe);
        raiz->balanco = alturaSubarvore(raiz->fd) - alturaSubarvore(raiz->fe);

        /* Atualizando a Raiz */
        raiz = novaRaiz;
        
    }

    return raiz;
}

struct nodo* balancear (struct nodo* novo){

    int coeficiente; //recebe o coef de balanco do nodo 'novo'

    coeficiente = novo->balanco;

    if (coeficiente > 1)
        novo = rotacaoParaEsquerda(novo);
    else if (coeficiente < -1)
        novo = rotacaoParaDireita(novo);

    return novo;
}

struct nodo* rotacaoParaEsquerda (struct nodo* raiz){

    struct nodo* novaRaiz; //a será a nova raiz
    struct nodo* paiAntigo; //referente ao pai da raiz passada como parametro
    struct nodo* aux;


    /* Caso que a rotacao eh na raiz e raiz->fd precisa de rotacao, mas para o lado oposto*/
    if ((raiz->pai == NULL) && (alturaSubarvore(raiz->fd->fd)-alturaSubarvore(raiz->fd->fe)) < 0)
        raiz->fd = rotacaoParaDireita(raiz->fd);
    else if ((raiz->fd->fd) == NULL) //caso de 'ZIGZAG'
    {
        aux = raiz->fd->fe;
        raiz->fd = aux;
        aux->pai->fd = NULL;
        aux->pai->fe = NULL;
        aux->fd = aux->pai;
        aux->fd->pai = aux;
        aux->pai = raiz;
    }

    paiAntigo = raiz->pai;
    novaRaiz = raiz->fd;
    raiz->fd = novaRaiz->fe;
    novaRaiz->pai = raiz->pai;
    raiz->pai = novaRaiz;

    if (novaRaiz->fe != NULL)
        novaRaiz->fe->pai = raiz;

    novaRaiz->fe = raiz;
    novaRaiz->fe->pai = novaRaiz;
    novaRaiz->fd->pai = novaRaiz;

    if (paiAntigo != NULL) //ou seja, nao se trata da raiz da arvore binaria
    { 
        if (paiAntigo->fe == raiz)
            novaRaiz->pai->fe = novaRaiz;
        else
            novaRaiz->pai->fd = novaRaiz;
    }
    
    /* Atualizando o balanco dos filhos da nova raiz */
    novaRaiz->fe->balanco = alturaSubarvore(novaRaiz->fe->fd) - alturaSubarvore(novaRaiz->fe->fe);
    novaRaiz->fd->balanco = alturaSubarvore(novaRaiz->fd->fd) - alturaSubarvore(novaRaiz->fd->fe);

    return novaRaiz;

}

struct nodo* rotacaoParaDireita (struct nodo* raiz) {

    struct nodo* novaRaiz; //a será a nova raiz
    struct nodo* paiAntigo; //referente ao pai da raiz passada como parametro
    struct nodo* aux;

    /* Caso que a rotacao eh na raiz e raiz->fd precisa de rotacao, mas para o lado oposto*/
    if ((raiz->pai == NULL) && (alturaSubarvore(raiz->fe->fd)-alturaSubarvore(raiz->fe->fe)) > 0)
        raiz->fe = rotacaoParaEsquerda(raiz->fe);
    else if ( (raiz->fe->fe) == NULL )  //caso de 'ZIGZAG'
    {
        aux = raiz->fe->fd;
        raiz->fe = aux;
        aux->pai->fd = NULL;
        aux->pai->fe = NULL;
        aux->fe = aux->pai;
        aux->fe->pai = aux;
        aux->pai = raiz;
    }

    paiAntigo = raiz->pai;
    novaRaiz = raiz->fe;
    raiz->fe = novaRaiz->fd;
    novaRaiz->pai = raiz->pai;

    raiz->pai = novaRaiz;
    if (novaRaiz->fd != NULL)
        novaRaiz->fd->pai = raiz;
    novaRaiz->fd = raiz;

    novaRaiz->fd->pai = novaRaiz;
    novaRaiz->fe->pai = novaRaiz;

    if (paiAntigo != NULL) //ou seja, nao se trata da raiz da arvore binaria
    { 
        if (paiAntigo->fd == raiz)
            novaRaiz->pai->fd = novaRaiz;
        else
            novaRaiz->pai->fe = novaRaiz;
    }

    /* Atualizando o balanco dos filhos da nova raiz */
    novaRaiz->fe->balanco = alturaSubarvore(novaRaiz->fe->fd) - alturaSubarvore(novaRaiz->fe->fe);
    novaRaiz->fd->balanco = alturaSubarvore(novaRaiz->fd->fd) - alturaSubarvore(novaRaiz->fd->fe);

    return novaRaiz;

}