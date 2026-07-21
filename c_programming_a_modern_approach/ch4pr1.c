#include <stdio.h>

int main(void) {
  int two_digit_number;

  printf("enter a two-digit number: ");
  scanf("%d", &two_digit_number);

  printf("the reversel is: %d%d\n", two_digit_number % 10, two_digit_number / 10);

  return 0;
}
