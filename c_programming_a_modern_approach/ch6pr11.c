#include <stdio.h>

int main(void) {
  double e = 1.0, factorial = 1.0;
  int i, number_of_terms;

  printf("Enter a number: ");
  scanf("%d", &number_of_terms);

  for (i = 1; i <= number_of_terms; i++) {
    factorial *= i;
    e += 1.0 / factorial;
  }

  printf("Approximation of e: %.10f\n", e);

  return 0;
}
