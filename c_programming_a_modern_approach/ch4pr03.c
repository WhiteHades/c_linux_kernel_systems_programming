#include <stdio.h>

int main(void) {
  int int_number;
  int d1, d2, d3, d4, d5; // octal - d1d2d3d4d5

  printf("enter num between 0 and 32767: ");
  scanf("%5d", &int_number);

  d5 = int_number % 8;
  d4 = (int_number / 8) % 8;
  d3 = (int_number / (8 * 8)) % 8;
  d2 = (int_number / (8 * 8 * 8)) % 8;
  d1 = (int_number / (8 * 8 * 8 * 8)) % 8;

  printf("in octal, your number is: %d%d%d%d%d\n", d1, d2, d3, d4, d5);

  return 0;
}
