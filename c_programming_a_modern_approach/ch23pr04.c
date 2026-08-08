#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_WORDS 100

int main(void) {
  char input[MAX_LINE_LENGTH + 2];
  char *words[MAX_WORDS];
  char *word;
  int count = 0;
  int i;

  printf("Enter a series of words: ");
  if (fgets(input, sizeof(input), stdin) == NULL)
    return 1;

  word = strtok(input, " \n");
  while (word != NULL) {
    if (count == MAX_WORDS) {
      printf("Too many words\n");
      return 1;
    }
    words[count++] = word;
    word = strtok(NULL, " \n");
  }

  for (i = count - 1; i >= 0; i--)
    printf("%s%s", words[i], i == 0 ? "\n" : " ");

  return 0;
}
