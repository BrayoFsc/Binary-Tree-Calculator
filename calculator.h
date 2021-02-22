#pragma once
// #ifndef __CALCULATOR__
// #define __CALCULATOR__

union key {
   char op = 0;
   float number;
};

struct node {
   bool is_op = false;
   key value;
   node *left, *right;
};

// lê a expressão de entrada dinamicamente alocada na memória
char *read(char *s);

// constrói a árvore binária com a expressão
node *buildtree(char *str, int *i);

// deleta a árvore binária
void delete_tree(node *no);

// imprimir a expressão lida
void print_expression(node *no);

// Verifica se o caractere é uma operação ou não
int isOp(char op);

// inicia o nodo
node *init(char *value, float isop);

// faz as expressões da árvore binária
node *calculate(node *no);

// Faz a operação indicada pelo nodo pai e os dois filhos
float operation(char op, float left, float right);

// #endif