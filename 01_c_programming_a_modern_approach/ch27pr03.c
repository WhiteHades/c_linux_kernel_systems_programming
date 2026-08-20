#include <complex.h>
#include <math.h>
#include <stdio.h>

int main(void) {
  double radius, theta;
  double complex number;
  double real_part;
  double imaginary_part;

  printf("Enter r and theta (radians): ");
  if (scanf("%lf%lf", &radius, &theta) != 2)
    return 1;

  number = radius * cexp(theta * I);
  real_part = creal(number);
  imaginary_part = cimag(number);
  if (fabs(real_part) < 1.0e-12)
    real_part = 0.0;
  if (fabs(imaginary_part) < 1.0e-12)
    imaginary_part = 0.0;
  printf("%g %c %gi\n", real_part, imaginary_part < 0.0 ? '-' : '+',
         fabs(imaginary_part));

  return 0;
}
