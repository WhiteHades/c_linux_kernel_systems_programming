#include <stdio.h>

int main(void) {
  int ch, character_count = 0, word_count = 0;
  int in_word = 0;

  printf("Enter a sentence: ");

  while ((ch = getchar()) != '\n' && ch != EOF) {
    if (ch != ' ') {
      character_count++;
      if (!in_word) {
        word_count++;
        in_word = 1;
      }
    } else {
      in_word = 0;
    }
  }

  printf("Average word length: %.1f\n",
         (double) character_count / word_count);

  return 0;
}
