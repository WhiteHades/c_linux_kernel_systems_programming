#include <stdio.h>

int main(void) {
  printf("size of int: %zu bytes\n", sizeof(int));
  printf("size of short: %zu bytes\n", sizeof(short));
  printf("size of long: %zu bytes\n", sizeof(long));
  printf("size of float: %zu bytes\n", sizeof(float));
  printf("size of double: %zu bytes\n", sizeof(double));
  printf("size of long double: %zu bytes\n", sizeof(long double));
}
