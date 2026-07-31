#include <stdio.h>

int main(void) {
  float largest = 0.0f, number;

  do {
    printf("Enter a number: ");
    scanf("%f", &number);

    if (number > largest)
      largest = number;
  } while (number > 0.0f);

  printf("The largest number entered was %.2f\n", largest);

  return 0;
}
