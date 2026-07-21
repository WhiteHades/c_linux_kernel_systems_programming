#include <stdio.h>

int main(void) {
  int i, number_of_entries, odd, square;

  printf("This program prints a table of squares.\n");
  printf("Enter number of entries in table: ");
  scanf("%d", &number_of_entries);

  for (i = 1, odd = 3, square = 1; i <= number_of_entries; i++, odd += 2) {
    printf("%10d%10d\n", i, square);
    square += odd;
  }

  return 0;
}
