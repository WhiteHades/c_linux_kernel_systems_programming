#include <stdio.h>

int main(void) {
  double e = 1.0, epsilon, term = 1.0;
  int i = 1;

  printf("Enter epsilon: ");
  scanf("%lf", &epsilon);

  if (epsilon <= 0.0) {
    printf("Epsilon must be positive\n");
    return 1;
  }

  while (1) {
    term /= i;

    if (term < epsilon)
      break;

    e += term;
    i++;
  }

  printf("Approximation of e: %.10f\n", e);

  return 0;
}
