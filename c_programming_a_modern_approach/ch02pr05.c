#include <stdio.h>

int main(void) 
{
  int polynomial_value;

  printf("enter the value of x: ");
  scanf("%d", &polynomial_value);

  int two = polynomial_value * polynomial_value; 
  int three = two * polynomial_value; 
  int four = two * two;
  int five = four * polynomial_value;
  int total = 3*five + 2*four - 5*three - two + 7*polynomial_value - 6;

  printf("value of the polynomial 3x^5 + 2x^4 - 5x^3 - x^2 + 7x - 6 is: %d\n", total);

  return 0;
}
