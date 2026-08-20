#include <math.h>
#include <stdio.h>

int main(void) {
  double a, b, c, discriminant, root1, root2;

  printf("Enter a, b, and c: ");
  if (scanf("%lf%lf%lf", &a, &b, &c) != 3) {
    printf("Invalid input\n");
    return 1;
  }

  if (a == 0.0) {
    printf("a must not be zero\n");
    return 1;
  }

  discriminant = b * b - 4.0 * a * c;
  if (discriminant < 0.0) {
    printf("The roots are complex.\n");
    return 0;
  }

  root1 = (-b + sqrt(discriminant)) / (2.0 * a);
  root2 = (-b - sqrt(discriminant)) / (2.0 * a);
  printf("x1 = %g\n", root1);
  printf("x2 = %g\n", root2);

  return 0;
}
