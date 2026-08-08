#include <ctype.h>
#include <stdio.h>

int main(void) {
  const int values[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
                          1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  int score = 0, ch;

  printf("Enter a word: ");
  while ((ch = getchar()) != '\n' && ch != EOF)
    if (isalpha((unsigned char)ch))
      score += values[toupper((unsigned char)ch) - 'A'];

  printf("Scrabble value: %d\n", score);
  return 0;
}
