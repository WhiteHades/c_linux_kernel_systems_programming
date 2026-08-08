#include <complex.h>
#include <math.h>
#include <stdio.h>

int main(void) {
  int n, k;
  double pi = acos(-1.0);

  printf("Enter a positive integer: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("n must be positive\n");
    return 1;
  }

  for (k = 0; k < n; k++) {
    double complex root = cexp((2.0 * pi * k / n) * I);
    double real_part = creal(root);
    double imaginary_part = cimag(root);

    if (fabs(real_part) < 1.0e-12)
      real_part = 0.0;
    if (fabs(imaginary_part) < 1.0e-12)
      imaginary_part = 0.0;
    printf("root %d = %g %c %gi\n", k, real_part,
           imaginary_part < 0.0 ? '-' : '+', fabs(imaginary_part));
  }

  return 0;
}
