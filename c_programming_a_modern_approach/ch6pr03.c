#include <stdio.h>

int main(void) {
  int numerator, denominator, first_number, second_number, remainder, gcd;

  printf("Enter a fraction: ");
  scanf("%d/%d", &numerator, &denominator);

  first_number = numerator;
  second_number = denominator;

  while (second_number != 0) {
    remainder = first_number % second_number;
    first_number = second_number;
    second_number = remainder;
  }

  gcd = first_number;

  printf("In lowest terms: %d/%d\n", numerator / gcd, denominator / gcd);

  return 0;
}
