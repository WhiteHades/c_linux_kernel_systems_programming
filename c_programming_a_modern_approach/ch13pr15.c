#include <ctype.h>
#include <stdio.h>

#define STACK_SIZE 100

int evaluate_RPN_expression(const char *expression);

int main(void) {
  char expression[201];

  printf("Enter an RPN expression: ");
  fgets(expression, sizeof(expression), stdin);
  printf("Value of expression: %d\n", evaluate_RPN_expression(expression));
  return 0;
}

int evaluate_RPN_expression(const char *expression) {
  int stack[STACK_SIZE], top = 0, left, right;

  while (*expression && *expression != '=') {
    if (isdigit((unsigned char) *expression)) {
      if (top == STACK_SIZE)
        return 0;
      stack[top++] = *expression - '0';
    } else if (*expression == '+' || *expression == '-' ||
               *expression == '*' || *expression == '/') {
      if (top < 2)
        return 0;
      right = stack[--top];
      left = stack[--top];
      switch (*expression) {
        case '+': stack[top++] = left + right; break;
        case '-': stack[top++] = left - right; break;
        case '*': stack[top++] = left * right; break;
        case '/': stack[top++] = left / right; break;
      }
    }
    expression++;
  }
  return top == 1 ? stack[0] : 0;
}
