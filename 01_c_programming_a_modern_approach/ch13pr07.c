#include <stdio.h>

int main(void) {
  const char *tens[] = {"", "", "twenty", "thirty", "forty", "fifty",
    "sixty", "seventy", "eighty", "ninety"};
  const char *ones[] = {"", "one", "two", "three", "four", "five", "six",
    "seven", "eight", "nine"};
  const char *teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen",
    "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
  int number;

  printf("Enter a two-digit number: ");
  scanf("%d", &number);
  if (number < 10 || number > 99) {
    printf("Number must have two digits.\n");
    return 1;
  }

  printf("You entered the number ");
  if (number < 20)
    printf("%s", teens[number - 10]);
  else {
    printf("%s", tens[number / 10]);
    if (number % 10)
      printf("-%s", ones[number % 10]);
  }
  printf(".\n");
  return 0;
}
