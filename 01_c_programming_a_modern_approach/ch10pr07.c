#include <stdio.h>

#define MAX_DIGITS 10
#define DIGIT_WIDTH 4

const int segments[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 1, 0, 1}, {1, 1, 1, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 1, 1}, {1, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 0, 1, 1}};
char digits[4][MAX_DIGITS * DIGIT_WIDTH];

void clear_digits_array(void);
void process_digit(int digit, int position);
void print_digits_array(void);

int main(void) {
  int ch, position = 0;

  clear_digits_array();
  printf("Enter a number: ");
  while ((ch = getchar()) != '\n' && ch != EOF && position < MAX_DIGITS)
    if (ch >= '0' && ch <= '9')
      process_digit(ch - '0', position++);
  print_digits_array();
  return 0;
}

void clear_digits_array(void) {
  for (int row = 0; row < 4; row++)
    for (int column = 0; column < MAX_DIGITS * DIGIT_WIDTH; column++)
      digits[row][column] = ' ';
}

void process_digit(int digit, int position) {
  const int segment_row[7] = {0, 1, 2, 3, 2, 1, 2};
  const int segment_column[7] = {1, 2, 2, 1, 0, 0, 1};
  const char segment_character[7] = {'_', '|', '|', '_', '|', '|', '_'};

  for (int segment = 0; segment < 7; segment++)
    if (segments[digit][segment])
      digits[segment_row[segment]][position * DIGIT_WIDTH +
                                   segment_column[segment]] =
          segment_character[segment];
}

void print_digits_array(void) {
  for (int row = 0; row < 4; row++) {
    for (int column = 0; column < MAX_DIGITS * DIGIT_WIDTH; column++)
      putchar(digits[row][column]);
    putchar('\n');
  }
}
