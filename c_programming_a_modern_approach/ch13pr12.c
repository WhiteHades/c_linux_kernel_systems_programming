#include <ctype.h>
#include <stdio.h>

#define MAX_WORDS 30
#define WORD_LEN 20

int main(void) {
  char words[MAX_WORDS][WORD_LEN + 1], ending = '\0';
  int ch, word_count = 0, length = 0, i;

  printf("Enter a sentence: ");
  while ((ch = getchar()) != '\n' && ch != EOF) {
    if (ch == '.' || ch == '?' || ch == '!') {
      ending = (char) ch;
      break;
    }
    if (isspace(ch)) {
      if (length > 0) {
        words[word_count++][length] = '\0';
        length = 0;
      }
    } else if (word_count < MAX_WORDS && length < WORD_LEN)
      words[word_count][length++] = (char) ch;
  }
  if (length > 0 && word_count < MAX_WORDS)
    words[word_count++][length] = '\0';

  printf("Reversal of sentence: ");
  for (i = word_count - 1; i >= 0; i--)
    printf("%s%s", words[i], i == 0 ? "" : " ");
  if (ending)
    putchar(ending);
  putchar('\n');
  return 0;
}
