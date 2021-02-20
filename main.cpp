#include <iostream>
#include <string>
using namespace std;

union key {
   char op = 0;
   float number;
};

struct node {
   bool is_op = false;
   key value;
   node *left, *right;
};

int isOp(char op)
{
   if (op == '+' || op == '-' || op == '*' || op == '/')
      return 1;
   return 0;
}

node *init(char *value, float isop)
{
   node *n = (node *)malloc(sizeof(node));
   if (isop)
   {
      n->is_op = true;
      n->value.op = value[0];
   } else
      n->value.number = atof((const char *)value);
   n->left = NULL;
   n->right = NULL;
   return n;
}

node *buildtree(char *str, int *i)
{
   node *node = NULL;

   if (str[*i] == '(')
   {
      char *number;
      number = (char *)malloc(30 * sizeof(char));
      int num = 0;

      (*i)++;
      if (isOp(str[*i]) && ((str[(*i) + 1] == ')') || (str[(*i) + 1] == '(')))
      {
         number[0] = str[*i];
         node = init(number, true);
         node->is_op = true;
         (*i)++;

      } else
      {
         for (; str[*i] != ')'; (*i)++)
         {
            number[num] = str[*i];
            num++;
         }
         node = init(number, false);
         node->is_op = false;
      }
      node->left = buildtree(str, i);
      node->right = buildtree(str, i);
      (*i)++;
      free(number);
   }
   return node;
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
   {
      if ((no->left != NULL) && (no->right != NULL))
      {
         cout << '(';
         print_expression(no->left);
         if (no->is_op)
            cout << no->value.op;
         else
            cout << no->value.number;
         print_expression(no->right);
         cout << ')';
      } else
      {
         print_expression(no->left);
         if (no->is_op)
            cout << no->value.op;
         else
            cout << no->value.number;
         print_expression(no->right);
      }
   }
}

node *calculate(node *no)
{
   if (no->value.number != NULL || no->value.op != NULL)
   {

      if (no->left->is_op)
         calculate(no->left);
      if (no->right->is_op)
         calculate(no->right);

      cout << no->left->value.number << no->value.op << no->right->value.number;
      if (no->is_op)
         no->value.number = operation(no->value.op, no->left->value.number, no->right->value.number);
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

int main()
{
   char *calc = NULL;
   calc = read(calc);

   node *no = NULL;
   int i = 0;
   no = buildtree(calc, &i);

   print_expression(no);
   cout << '\n';

   no = calculate(no);
   cout << no->value.number;
}
