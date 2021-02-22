#include "calculator.cpp"

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
   delete_tree(no);
   free(calc);
   calc = NULL;
}
