#include <stdio.h>

int main(void) {
  int first_number, second_number, remainder;

  printf("Enter two integers: ");
  scanf("%d%d", &first_number, &second_number);

  while (second_number != 0) {
    remainder = first_number % second_number;
    first_number = second_number;
    second_number = remainder;
  }

  printf("Greatest common divisor: %d\n", first_number);

  return 0;
}
