#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "avl.h"

int comando()
{

    char linhaComando[5];
    char* operacao;
    long int valor;
    long int output;
    char* token;
    char* aux;

    printf("Formato de comando aceito: <operacao> <valor>. Sendo:\n");
    printf("Operacoes:\n    - i: inserir\n");
    printf("    - r: remover\n");
    printf("    - b: busca\n");
    printf("    - e: imprimir em ordem\n");
    printf("    - l: imprimir em largura\n");
    printf("    - f: finalizar\n");
    printf("Valor: valor inteiro, aceito para as funcoes i, r e b\n");

    scanf("%[^\n]", linhaComando);
    getchar() ; 

    if ((linhaComando[1]) && (linhaComando[1] != ' '))
    {
        printf("Erro: comando inválido\n");
        printf("Formato de comando aceito: <operacao> <valor>. Sendo:\n");
        printf("Operacoes:\n    - i: inserir\n");
        printf("    - r: remover\n");
        printf("    - b: busca\n");
        printf("    - e: imprimir em ordem\n");
        printf("    - l: imprimir em largura\n");
        printf("    - f: finalizar\n");
        printf("Valor: valor inteiro, aceito para as funcoes i, r e b\b");
        exit(1);
    }

    /* aux servirá para percorrer os token formados a partir da linha de comando*/
    aux = strtok(linhaComando, " ");

    
    /* operacao recebe o primeiro caracter da linha de comando,
    correspondente ao tipo de funcao que se deseja executar */
    operacao = aux;

    output = 0;
    switch (*operacao) {
        case 'i':

            /* Assumindo que haja casos em que operacao e valor
            estao separados por mais de um space */
            while(aux)
            {
                /* obtendo o proximo token */
                aux = strtok(NULL, " ");

                /* evita que token receba "EOF" */
                if (aux != NULL)
                    token = aux;
            }


            /* Transformando o caracter em seu respectivo valor inteiro*/
            valor = strtol(token, NULL, 10);

            /* No decorrer do codigo utilizarei 
            [(valor*10)+1]/10  = (valor*10) como valor da variavel
            e [(valor*10)+1]%10 = 1 como identificador da funcao inserir */
            output = (valor*10)+1;

            break;
        
        case 'r':

            /* Assumindo que haja casos em que operacao e valor
            estao separados por mais de um space */
            while(aux)
            {
                /* obtendo o proximo token */
                aux = strtok(NULL, " ");

                /* evita que token receba "EOF" */
                if (aux != NULL)
                    token = aux;
            }

            /* Transformando o caracter em seu respectivo valor inteiro*/
            valor = strtol(token, NULL, 10);

            /* No decorrer do codigo utilizarei
            [(valor*10)+2]/10 = (valor*10)como valor da variavel
            e [(valor*10)+2]%10 = 2 como identificador da funcao excluir */
            output = (valor*10)+2;

            break;            

        case 'b':

             /* Assumindo que haja casos em que operacao e valor
            estao separados por mais de um space */
            while(aux)
            {
                /* obtendo o proximo token */
                aux = strtok(NULL, " ");

                /* evita que token receba "EOF" */
                if (aux != NULL)
                    token = aux;
            }

            /* Transformando o caracter em seu respectivo valor inteiro*/
            valor = strtol(token, NULL, 10);

            /* No decorrer do codigo utilizarei
            [(valor*10)+3]/10 = (valor*10)como valor da variavel
            e [(valor*10)+3]%10 = 3 como identificador da funcao buscar */
            output = (valor*10)+3;

            break;

        case 'e':
            output = 4;
            break;

        case 'l':
            output = 5;
            break;

        case 'f':
            output = 6;
            break;
        
        default:
            printf("Erro: comando inválido\n");
            printf("Formato de comando aceito: <operacao> <valor>. Sendo:\n");
            printf("Operacoes:\n    - i: inserir\n");
            printf("    - r: remover\n");
            printf("    - b: busca\n");
            printf("    - e: imprimir em ordem\n");
            printf("    - l: imprimir em largura\n");
            printf("    - f: finalizar\n");
            printf("Valor: valor inteiro, aceito para as funcoes i, r e b\b");
            exit(1);
            break;
    }

    return output;
}

void operacoes() {

    long int execucao;
	int op;
	int valor;

    execucao = comando();

    /* Inicializando a arvore */
    struct arvore* Tree = malloc(sizeof(struct arvore));
    if (!(Tree))
    {
        printf("Nao foi possivel alocar a Arvore.\n");
        exit(1);
    }
	Tree->tam = 0;
	Tree->raiz = NULL;

	/* op recebe a identificacao da operacao*/
	op = execucao % 10;

	/* Variavel valor recebe o valor passado na linha de comando */
	valor = execucao / 10;

	while (op != 6) {
		
		switch (op) {

            /* Caso de Inserção*/
			case 1:
            {
                struct nodo* outputInserir;
				if ((outputInserir = inserir(&Tree->raiz, valor)) != NULL)
                {
                    Tree->raiz = outputInserir;
                }
                Tree->raiz = atualizarRaiz(Tree->raiz);
				break;
            }

            /* Caso de Excluir */
			case 2:
            {
                int outputExcluir;
                if ((outputExcluir = excluir(&Tree->raiz, valor)) == 0)
                    printf("Falha ao remover %i.\n", valor);
                Tree->raiz = atualizarRaiz(Tree->raiz);             
                break;
            }

            /* Caso de Busca */
			case 3:
            {
                struct nodo* saida = buscar(Tree->raiz, valor);
                if (saida != NULL)
                    printf("Encontrado %i\n", saida->chave);
                else
                    printf("Nodo nao encontrado!\n");

                /* Desalocando memoria*/
                saida = NULL;
                free(saida);

                break;
            }

            /* Cado de Imprimir em Ordem */
			case 4:
				imprimirEmOrdem(Tree->raiz);
                printf("\n");
				break;

            /* Caso de Imprimir em Largura */
			case 5:
                imprimirEmLargura(Tree->raiz);
				break;
		}


        execucao = comando();
		op = execucao % 10;
		valor = execucao / 10;
	}
}