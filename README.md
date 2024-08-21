# Projeto de Implementação de Árvore Binária e AVL em C

Este repositório contém a implementação de duas estruturas de dados fundamentais: uma **Árvore Binária de Busca** e uma **Árvore AVL**. Ambas as implementações foram desenvolvidas em C como parte de um projeto acadêmico durante a disciplina de Algoritmos e Estruturas de Dados, com o objetivo de explorar e entender as diferenças entre essas duas estruturas de dados, especialmente no que tange ao balanceamento automático das árvores AVL.

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos:

- **`main.c`**: Arquivo principal que contém a função `main`. Este arquivo gerencia a execução do programa e faz chamadas para as funções implementadas nas árvores.
- **`avl.c` e `avl.h`**: Arquivos que contêm a implementação e a definição da árvore AVL. A árvore AVL é uma árvore binária de busca auto-balanceada, onde as alturas das subárvores esquerda e direita de qualquer nó diferem em no máximo um.
- **`arvore_binaria.c`**: Implementação da árvore binária de busca, onde não há balanceamento automático.
- **`menu.c` e `menu.h`**: Arquivos que implementam e definem o menu de interações com o usuário. O menu permite realizar operações como inserção, remoção e busca de elementos em ambas as árvores.
- **`fila.c` e `fila.h`**: Implementação de uma fila auxiliar utilizada para operações que requerem um controle sequencial de elementos (como travessia em largura).
- **`makefile`**: Script utilizado para automatizar o processo de compilação do projeto. Ele gera o executável a partir dos arquivos `.c` e `.h` fornecidos.

## Funcionalidades Implementadas

### Árvore Binária de Busca

A Árvore Binária de Busca permite as seguintes operações:

- **Inserção**: Adiciona um novo nó à árvore seguindo as regras de ordenação.
- **Remoção**: Remove um nó específico da árvore, reorganizando os nós remanescentes conforme necessário.
- **Busca**: Pesquisa um valor específico dentro da árvore.

### Árvore AVL

A Árvore AVL, além das operações da Árvore Binária de Busca, realiza operações adicionais para garantir o balanceamento automático:

- **Rotação**: As rotações simples e duplas (à esquerda e à direita) são utilizadas para manter o balanceamento da árvore após inserções e remoções.
- **Verificação de Altura**: Mantém a altura de cada nó e utiliza essas informações para determinar se uma rotação é necessária.

## Compilação e Execução

### Requisitos

- Um compilador C (como `gcc`).

### Como Compilar

Para compilar o projeto, utilize o `makefile` incluído. No terminal, dentro do diretório do projeto, execute:

```bash
make
```
Este comando irá compilar todos os arquivos .c e gerar um executável.

### Como Executar

Após a compilação, execute o programa gerado:
```bash
./exec
```

## Utilização

Após executar o programa, você será apresentado a um menu onde poderá:
1. **Inserir** um novo elemento na Árvore Binária ou AVL.
2. **Remover** um elemento existente.
3. **Buscar** por um elemento.
4. **Exibir** a árvore em:
   - ordem,
   - pré-ordem, ou
   - pós-ordem.
5. **Sair** do programa.

