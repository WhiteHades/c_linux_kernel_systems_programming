#include <stdio.h>

int main(void) {
  int occurrences[10] = {0};
  long number;

  printf("Enter a number: ");
  scanf("%ld", &number);

  do {
    occurrences[number % 10]++;
    number /= 10;
  } while (number > 0);

  printf("Digit:       ");
  for (int digit = 0; digit < 10; digit++)
    printf(" %d", digit);
  printf("\nOccurrences: ");
  for (int digit = 0; digit < 10; digit++)
    printf(" %d", occurrences[digit]);
  printf("\n");

  return 0;
}
