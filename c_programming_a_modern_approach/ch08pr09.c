#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

int main(void) {
  char walk[SIZE][SIZE];
  int row = 0, column = 0;
  const int row_change[4] = {-1, 0, 1, 0};
  const int column_change[4] = {0, 1, 0, -1};

  srand((unsigned)time(NULL));
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      walk[i][j] = '.';
  walk[row][column] = 'A';

  for (char letter = 'B'; letter <= 'Z'; letter++) {
    int directions[4] = {0, 1, 2, 3};
    bool moved = false;

    for (int i = 3; i > 0; i--) {
      int j = rand() % (i + 1);
      int temp = directions[i];
      directions[i] = directions[j];
      directions[j] = temp;
    }
    for (int i = 0; i < 4; i++) {
      int direction = directions[i];
      int next_row = row + row_change[direction];
      int next_column = column + column_change[direction];
      if (next_row >= 0 && next_row < SIZE && next_column >= 0 &&
          next_column < SIZE && walk[next_row][next_column] == '.') {
        row = next_row;
        column = next_column;
        walk[row][column] = letter;
        moved = true;
        break;
      }
    }
    if (!moved)
      break;
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++)
      printf("%c ", walk[i][j]);
    printf("\n");
  }

  return 0;
}
