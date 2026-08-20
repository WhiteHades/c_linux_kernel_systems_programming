#include <stdio.h>

long long power(long long x, unsigned int n);

int main(void) {
  long long x;
  unsigned int n;

  printf("Enter x and n: ");
  scanf("%lld%u", &x, &n);
  printf("Result: %lld\n", power(x, n));
  return 0;
}

long long power(long long x, unsigned int n) {
  if (n == 0)
    return 1;
  if (n % 2 == 0) {
    long long half = power(x, n / 2);
    return half * half;
  }
  return x * power(x, n - 1);
}
