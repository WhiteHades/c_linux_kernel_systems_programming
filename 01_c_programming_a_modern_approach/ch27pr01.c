#include <complex.h>
#include <math.h>
#include <stdio.h>

static void print_complex_root(const char *name, double complex root) {
  double real_part = creal(root);
  double imaginary_part = cimag(root);

  printf("%s = %g %c %gi\n", name, real_part,
         imaginary_part < 0.0 ? '-' : '+', fabs(imaginary_part));
}

int main(void) {
  double a, b, c, discriminant;

  printf("Enter a, b, and c: ");
  if (scanf("%lf%lf%lf", &a, &b, &c) != 3)
    return 1;
  if (a == 0.0) {
    printf("a must not be zero\n");
    return 1;
  }

  discriminant = b * b - 4.0 * a * c;
  if (discriminant >= 0.0) {
    double square_root = sqrt(discriminant);

    printf("root1 = %g\n", (-b + square_root) / (2.0 * a));
    printf("root2 = %g\n", (-b - square_root) / (2.0 * a));
  } else {
    double complex square_root = csqrt(discriminant + 0.0 * I);

    print_complex_root("root1", (-b + square_root) / (2.0 * a));
    print_complex_root("root2", (-b - square_root) / (2.0 * a));
  }

  return 0;
}
