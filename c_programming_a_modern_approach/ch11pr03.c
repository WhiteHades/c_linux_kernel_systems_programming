#include <stdio.h>

void reduce(int numerator, int denominator, int *reduced_numerator,
            int *reduced_denominator);

int main(void) {
  int numerator, denominator, reduced_numerator, reduced_denominator;

  printf("Enter a fraction: ");
  scanf("%d/%d", &numerator, &denominator);
  reduce(numerator, denominator, &reduced_numerator, &reduced_denominator);
  printf("In lowest terms: %d/%d\n", reduced_numerator,
         reduced_denominator);
  return 0;
}

void reduce(int numerator, int denominator, int *reduced_numerator,
            int *reduced_denominator) {
  int a = numerator, b = denominator;
  while (b != 0) {
    int remainder = a % b;
    a = b;
    b = remainder;
  }
  if (a < 0)
    a = -a;
  *reduced_numerator = numerator / a;
  *reduced_denominator = denominator / a;
  if (*reduced_denominator < 0) {
    *reduced_numerator = -*reduced_numerator;
    *reduced_denominator = -*reduced_denominator;
  }
}
