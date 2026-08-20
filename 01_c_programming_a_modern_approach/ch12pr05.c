#include <stdio.h>

#define MAX_SENTENCE 100

int main(void) {
  char sentence[MAX_SENTENCE], *position = sentence, terminator;
  int ch;

  printf("Enter a sentence: ");
  while (position < sentence + MAX_SENTENCE && (ch = getchar()) != '.' &&
         ch != '?' && ch != '!' && ch != '\n' && ch != EOF)
    *position++ = (char)ch;
  terminator = (ch == '.' || ch == '?' || ch == '!') ? (char)ch : '.';

  printf("Reversal of sentence:");
  while (position > sentence) {
    while (position > sentence && position[-1] == ' ')
      position--;
    char *end = position;
    while (position > sentence && position[-1] != ' ')
      position--;
    if (position < end) {
      putchar(' ');
      for (char *word = position; word < end; word++)
        putchar(*word);
    }
  }
  printf("%c\n", terminator);
  return 0;
}
