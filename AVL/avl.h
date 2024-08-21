#ifndef AVL_H_
#define AVL_H_

#include <stdlib.h>

struct nodo {
    int chave;
    int balanco;
    int alturadoNodo;
    struct nodo* pai;
    struct nodo* fe;
    struct nodo* fd;
};

struct arvore {
    size_t tam;
    struct nodo* raiz;
};

struct aluno{
    char* nome;//nome completo
    char* nomeDinf;//nome de usuário nas servidoras do dinf
    unsigned int grr;
};

struct aluno* getAluno1();

//retorne NULL se o aluno2 não existir
struct aluno* getAluno2();

void imprimirDadosAlunos();

//retorna NULL se não foi possível inserir
struct nodo* inserir(struct nodo** raiz, int chave);

//retorna 1 caso removido, ou 0 caso não seja possível remover
int excluir(struct nodo** raiz, int chave);

//transplanta os nodos de forma que B fica no lugar do A
void transplantar(struct nodo* raiz, struct nodo* A, struct nodo* B);

//retorna o nodo antecessor do nodo passado como parametro
struct nodo* buscaAntecessor(struct nodo* x);

//retorna NULL se não existe
struct nodo* buscar(struct nodo* nodo, int chave);

//imprime a arvore em ordem
void imprimirEmOrdem(struct nodo* nodo);

//imprime a arvore em largura
void imprimirEmLargura(struct nodo* raiz);

//retorna a altura do nodo em relacao a raiz
int alturaNodo(struct nodo* aux);

//retorna a altura da subarvore passada como parametro
int alturaSubarvore(struct nodo* nodo);

/* Atualiza o balaco dos nodos */
void atualizarBalanco(struct nodo* nodo);

// retorna a raiz após ela ser balanceada
struct nodo* atualizarRaiz(struct nodo* raiz);

/* Realiza o balanceamento analisando qual caso se encaixa (eqs, dir),
retornando o ponteiro para a nova raiz */
struct nodo* balancear (struct nodo* novo);

/*realiza uma rotacao a esquerda no nodo passado por parametro
e retorna o ponteiro para a nova raiz da subArvore em questao*/
struct nodo* rotacaoParaEsquerda(struct nodo* novo);

/*realiza uma rotacao a direita no nodo passado por parametro
e retorna o ponteiro para a nova raiz da subArvore em questao*/
struct nodo* rotacaoParaDireita(struct nodo* novo);

#endif // AVL_H_