#include <stdio.h>

int main(void) {
  int number;

  printf("Enter a positive integer: ");
  scanf("%d", &number);

  printf("The reversal is: ");

  do {
    printf("%d", number % 10);
    number /= 10;
  } while (number > 0);

  printf("\n");

  return 0;
}
