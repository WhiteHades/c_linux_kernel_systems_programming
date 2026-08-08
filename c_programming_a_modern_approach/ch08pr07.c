#include <stdio.h>

#define SIZE 5

int main(void) {
  int values[SIZE][SIZE], row_totals[SIZE] = {0}, column_totals[SIZE] = {0};

  for (int row = 0; row < SIZE; row++) {
    printf("Enter row %d: ", row + 1);
    for (int column = 0; column < SIZE; column++) {
      scanf("%d", &values[row][column]);
      row_totals[row] += values[row][column];
      column_totals[column] += values[row][column];
    }
  }

  printf("Row totals:");
  for (int row = 0; row < SIZE; row++)
    printf(" %d", row_totals[row]);
  printf("\nColumn totals:");
  for (int column = 0; column < SIZE; column++)
    printf(" %d", column_totals[column]);
  printf("\n");

  return 0;
}
