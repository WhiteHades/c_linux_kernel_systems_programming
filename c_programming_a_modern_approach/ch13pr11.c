#include <ctype.h>
#include <stdio.h>

double compute_average_word_length(const char *sentence);

int main(void) {
  char sentence[201];

  printf("Enter a sentence: ");
  fgets(sentence, sizeof(sentence), stdin);
  printf("Average word length: %.1f\n",
         compute_average_word_length(sentence));
  return 0;
}

double compute_average_word_length(const char *sentence) {
  int characters = 0, words = 0, in_word = 0;

  while (*sentence && *sentence != '\n') {
    if (isspace((unsigned char) *sentence))
      in_word = 0;
    else {
      characters++;
      if (!in_word) {
        words++;
        in_word = 1;
      }
    }
    sentence++;
  }
  return words == 0 ? 0.0 : (double) characters / words;
}
