#include <stdio.h>

long polynomial(long x);

int main(void) {
  long x;

  printf("Enter a value for x: ");
  scanf("%ld", &x);
  printf("Polynomial value: %ld\n", polynomial(x));
  return 0;
}

long polynomial(long x) {
  return ((((3 * x + 2) * x - 5) * x - 1) * x + 7) * x - 6;
}
