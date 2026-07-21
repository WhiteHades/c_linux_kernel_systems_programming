#include <stdio.h>

int main(void) {
  int number;
  printf("enter a number: ");
  scanf("%d", &number);

  if (number >= 0 && number <= 9)
    return printf("the number %d has 1 digit\n", number);
  else if (number >= 10 && number <= 99)
    return printf("the number %d has 2 digits\n", number);
  else if (number >= 100 && number <= 999)
    return printf("the number %d has 3 digits\n", number);
  else
    return printf("the number %d has 4 digits\n", number);

  return 0;
}
