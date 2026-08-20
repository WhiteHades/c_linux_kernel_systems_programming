#include <float.h>
#include <limits.h>
#include <stdio.h>

int main(void) {
  int n, i;
  short short_factorial = 1;
  int int_factorial = 1;
  long long_factorial = 1;
  long long long_long_factorial = 1;
  float float_factorial = 1.0f;
  double double_factorial = 1.0;
  long double long_double_factorial = 1.0L;
  int short_overflow = 0, int_overflow = 0, long_overflow = 0;
  int long_long_overflow = 0, float_overflow = 0, double_overflow = 0;
  int long_double_overflow = 0;

  printf("Enter a positive integer: ");
  scanf("%d", &n);

  for (i = 2; i <= n; i++) {
    if (!short_overflow) {
      if (short_factorial > SHRT_MAX / i)
        short_overflow = 1;
      else
        short_factorial *= i;
    }

    if (!int_overflow) {
      if (int_factorial > INT_MAX / i)
        int_overflow = 1;
      else
        int_factorial *= i;
    }

    if (!long_overflow) {
      if (long_factorial > LONG_MAX / i)
        long_overflow = 1;
      else
        long_factorial *= i;
    }

    if (!long_long_overflow) {
      if (long_long_factorial > LLONG_MAX / i)
        long_long_overflow = 1;
      else
        long_long_factorial *= i;
    }

    if (!float_overflow) {
      if (float_factorial > FLT_MAX / i)
        float_overflow = 1;
      else
        float_factorial *= i;
    }

    if (!double_overflow) {
      if (double_factorial > DBL_MAX / i)
        double_overflow = 1;
      else
        double_factorial *= i;
    }

    if (!long_double_overflow) {
      if (long_double_factorial > LDBL_MAX / i)
        long_double_overflow = 1;
      else
        long_double_factorial *= i;
    }
  }

  if (short_overflow)
    printf("short: overflow\n");
  else
    printf("short: %hd\n", short_factorial);

  if (int_overflow)
    printf("int: overflow\n");
  else
    printf("int: %d\n", int_factorial);

  if (long_overflow)
    printf("long: overflow\n");
  else
    printf("long: %ld\n", long_factorial);

  if (long_long_overflow)
    printf("long long: overflow\n");
  else
    printf("long long: %lld\n", long_long_factorial);

  if (float_overflow)
    printf("float: overflow\n");
  else
    printf("float: %g\n", float_factorial);

  if (double_overflow)
    printf("double: overflow\n");
  else
    printf("double: %g\n", double_factorial);

  if (long_double_overflow)
    printf("long double: overflow\n");
  else
    printf("long double: %Lg\n", long_double_factorial);

  return 0;
}
