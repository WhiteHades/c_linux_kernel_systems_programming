#include <stdbool.h>
#include <stdio.h>

int main(void) {
  long number;

  for (;;) {
    bool seen[10] = {false};
    bool repeated = false;

    printf("Enter a number: ");
    scanf("%ld", &number);
    if (number <= 0)
      break;

    while (number > 0) {
      int digit = number % 10;
      if (seen[digit])
        repeated = true;
      seen[digit] = true;
      number /= 10;
    }
    printf(repeated ? "Repeated digit\n" : "No repeated digit\n");
  }

  return 0;
}
