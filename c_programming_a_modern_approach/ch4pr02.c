#include <stdio.h>

int main(void) {
  int three_digit_number;

  printf("enter a three-digit number: ");
  scanf("%d", &three_digit_number);

  int two_digit_number = (three_digit_number % 100);

  printf("the reversel is: %d%d%d\n", two_digit_number % 10, two_digit_number / 10,
         three_digit_number / 100);

  return 0;
}
