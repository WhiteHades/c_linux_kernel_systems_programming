#include <stdio.h>

#define MAX_SENTENCE 100

int main(void) {
  char sentence[MAX_SENTENCE], terminator;
  int length = 0, ch;

  printf("Enter a sentence: ");
  while (length < MAX_SENTENCE && (ch = getchar()) != '.' && ch != '?' &&
         ch != '!' && ch != '\n' && ch != EOF)
    sentence[length++] = (char)ch;
  terminator = (ch == '.' || ch == '?' || ch == '!') ? (char)ch : '.';

  printf("Reversal of sentence:");
  for (int end = length; end > 0;) {
    while (end > 0 && sentence[end - 1] == ' ')
      end--;
    int start = end;
    while (start > 0 && sentence[start - 1] != ' ')
      start--;
    if (start < end) {
      putchar(' ');
      for (int i = start; i < end; i++)
        putchar(sentence[i]);
    }
    end = start;
  }
  printf("%c\n", terminator);

  return 0;
}
