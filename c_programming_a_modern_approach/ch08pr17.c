#include <stdio.h>

int main(void) {
  int n;

  printf("This program creates a magic square of a specified size.\n");
  printf("The size must be an odd number between 1 and 99.\n");
  printf("Enter size of magic square: ");
  scanf("%d", &n);
  if (n < 1 || n > 99 || n % 2 == 0) {
    printf("Invalid size\n");
    return 1;
  }

  int square[n][n];
  for (int row = 0; row < n; row++)
    for (int column = 0; column < n; column++)
      square[row][column] = 0;

  int row = 0, column = n / 2;
  for (int value = 1; value <= n * n; value++) {
    square[row][column] = value;
    int next_row = (row + n - 1) % n;
    int next_column = (column + 1) % n;
    if (square[next_row][next_column] != 0)
      row = (row + 1) % n;
    else {
      row = next_row;
      column = next_column;
    }
  }

  for (row = 0; row < n; row++) {
    for (column = 0; column < n; column++)
      printf("%5d", square[row][column]);
    printf("\n");
  }

  return 0;
}
