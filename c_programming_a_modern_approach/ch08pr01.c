#include <stdbool.h>
#include <stdio.h>

int main(void) {
  bool seen[10] = {false}, repeated[10] = {false};
  long number;

  printf("Enter a number: ");
  scanf("%ld", &number);

  do {
    int digit = number % 10;
    if (seen[digit])
      repeated[digit] = true;
    seen[digit] = true;
    number /= 10;
  } while (number > 0);

  printf("Repeated digit(s):");
  for (int digit = 0; digit < 10; digit++)
    if (repeated[digit])
      printf(" %d", digit);
  printf("\n");

  return 0;
}
