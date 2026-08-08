#include <stdio.h>

void create_magic_square(int n, int magic_square[n][n]);
void print_magic_square(int n, int magic_square[n][n]);

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

  int magic_square[n][n];
  create_magic_square(n, magic_square);
  print_magic_square(n, magic_square);
  return 0;
}

void create_magic_square(int n, int magic_square[n][n]) {
  for (int row = 0; row < n; row++)
    for (int column = 0; column < n; column++)
      magic_square[row][column] = 0;

  int row = 0, column = n / 2;
  for (int value = 1; value <= n * n; value++) {
    magic_square[row][column] = value;
    int next_row = (row + n - 1) % n;
    int next_column = (column + 1) % n;
    if (magic_square[next_row][next_column] != 0)
      row = (row + 1) % n;
    else {
      row = next_row;
      column = next_column;
    }
  }
}

void print_magic_square(int n, int magic_square[n][n]) {
  for (int row = 0; row < n; row++) {
    for (int column = 0; column < n; column++)
      printf("%5d", magic_square[row][column]);
    printf("\n");
  }
}
