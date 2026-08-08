#include <complex.h>
#include <stdio.h>

int main(void) {
  double real_part, imaginary_part;
  double complex number;

  printf("Enter a and b: ");
  if (scanf("%lf%lf", &real_part, &imaginary_part) != 2)
    return 1;

  number = real_part + imaginary_part * I;
  printf("r = %g\n", cabs(number));
  printf("theta = %g radians\n", carg(number));

  return 0;
}
