#include <math.h>
#include <stdio.h>

int main(void) {
  double old_y, x, y = 1.0;

  printf("Enter a positive number: ");
  scanf("%lf", &x);

  do {
    old_y = y;
    y = (old_y + x / old_y) / 2.0;
  } while (fabs(y - old_y) >= .00001 * y);

  printf("Square root: %g\n", y);

  return 0;
}
