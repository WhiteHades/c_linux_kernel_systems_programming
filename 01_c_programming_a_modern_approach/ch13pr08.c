#include <ctype.h>
#include <stdio.h>

int compute_scrabble_value(const char *word);

int main(void) {
  char word[101];

  printf("Enter a word: ");
  scanf("%100s", word);
  printf("Scrabble value: %d\n", compute_scrabble_value(word));
  return 0;
}

int compute_scrabble_value(const char *word) {
  const int values[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
    1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  int total = 0;

  while (*word) {
    if (isalpha((unsigned char) *word))
      total += values[toupper((unsigned char) *word) - 'A'];
    word++;
  }
  return total;
}
