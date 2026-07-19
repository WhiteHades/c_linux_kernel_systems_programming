#include <stdio.h>

int main(void)
{
  float amount;

  printf("enter an amount: ");
  scanf("%f", &amount);
  printf("with tax added: $%.2f\n", amount * 1.05);

  return 0;
}
