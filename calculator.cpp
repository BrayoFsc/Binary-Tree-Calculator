#include "calculator.h"
#include <iostream>
#include <string>
using namespace std;

int isOp(char op)
{
   if (op == '+' || op == '-' || op == '*' || op == '/')
      return 1;
   return 0;
}

node *init(char *value, float isop)
{
   // armazena a memória para o nodo
   node *n = (node *)malloc(sizeof(node));
   if (isop) // verifica se é uma operação para deixar o flag da struct marcado
   {
      n->is_op = true;
      n->value.op = value[0];
   } else /// converte a string para float e atribui ela à variavel
      n->value.number = atof((const char *)value);
   n->left = NULL;
   n->right = NULL;
   return n;
}

node *buildtree(char *str, int *i)
{
   node *node = NULL;
   // a cada "(", um novo nodo é criado para armazenar o próximo número ou operação
   if (str[*i] == '(')
   {
      char *number; // string provissória
      number = (char *)malloc(30 * sizeof(char));
      int num = 0;

      (*i)++;
      if (isOp(str[*i]) && ((str[(*i) + 1] == ')') || (str[(*i) + 1] == '(')))
      { // se for uma operação, e o proximo caractere não for um número, quer dizer que é uma operação e não um número negativo por exemplo
         number[0] = str[*i];
         node = init(number, true);
         (*i)++;

      } else
      { // caso contrário, é um número, então armazena cada caractere numa string até se achar o final dado por ")"
         for (; str[*i] != ')'; (*i)++)
         {
            number[num] = str[*i];
            num++;
         }
         node = init(number, false);
      }
      node->left = buildtree(str, i);
      node->right = buildtree(str, i);
      (*i)++;

      free(number);
      number = NULL;
   }
   return node;
}
void delete_tree(node *no)
{
   if (no != NULL)
   {
      delete_tree(no->left);
      delete_tree(no->right);
      free(no);
   }
}

float operation(char op, float left, float right)
{
   switch (op)
   {
   case '+':
      return (left + right);
      break;
   case '-':
      return (left - right);
      break;
   case '*':
      return (left * right);
      break;
   case '/':
      return (left / right);
      break;
   default:
      return 0;
      break;
   }
}

void print_expression(node *no)
{
   if (no != NULL)
   { // se for uma operação, isola ela com parenteses para respeitar a ordem da conta
      if (no->is_op)
      {
         cout << '(';
         print_expression(no->left);
         cout << no->value.op;
         print_expression(no->right);
         cout << ')';
      } else
      {
         print_expression(no->left);
         cout << no->value.number;
         print_expression(no->right);
      }
   }
}

node *calculate(node *no)
{
   // o calculate só é chamado com nodos que são operações, então não é necessário que se verifique isso
   if (no != NULL)
   {
      // verifica se há operações para serem feitas antes
      if (no->left->is_op)
         calculate(no->left);
      if (no->right->is_op)
         calculate(no->right);
      // imprime a operação que está sendo feita
      cout << no->left->value.number << no->value.op << no->right->value.number;
      // atribui o numero à operação, abaixa a flag e imprime o resultado ao lado da operação
      no->value.number = operation(no->value.op, no->left->value.number, no->right->value.number);
      no->is_op = false;
      cout << " = " << no->value.number;
      cout << '\n';
   }
   free(no->right);
   no->right = NULL;
   free(no->left);
   no->left = NULL;
   return no;
}

char *read(char *s)
{
   int size = 0, i = 0;
   int ch, base = 5;

   while (ch != '\n')
   {
      ch = getc(stdin);
      if (size <= i)
      {
         size += base;
         s = (char *)realloc(s, size);
      }
      s[i] = ch;
      i++;
   }
   return s;
}
