#include <stdio.h>

int main(void) {
  double operand, value;
  int op;

  printf("Enter an expression: ");
  scanf("%lf", &value);

  while ((op = getchar()) != '\n' && op != EOF) {
    scanf("%lf", &operand);

    switch (op) {
    case '+':
      value += operand;
      break;
    case '-':
      value -= operand;
      break;
    case '*':
      value *= operand;
      break;
    case '/':
      value /= operand;
      break;
    default:
      printf("Invalid operator\n");
      return 1;
    }
  }

  printf("Value of expression: %g\n", value);

  return 0;
}
