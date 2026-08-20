#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 50
#define WORD_LEN 20

int main(void) {
  char *words[MAX_WORDS], input[WORD_LEN + 1], *copy;
  int count = 0, i, j;

  while (count < MAX_WORDS) {
    printf("Enter word: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
      break;
    input[strcspn(input, "\n")] = '\0';
    if (input[0] == '\0')
      break;
    copy = malloc(strlen(input) + 1);
    if (copy == NULL) {
      printf("No space left.\n");
      break;
    }
    strcpy(copy, input);
    words[count++] = copy;
  }

  for (i = 1; i < count; i++) {
    copy = words[i];
    for (j = i; j > 0 && strcmp(words[j - 1], copy) > 0; j--)
      words[j] = words[j - 1];
    words[j] = copy;
  }
  printf("In sorted order:");
  for (i = 0; i < count; i++) {
    printf(" %s", words[i]);
    free(words[i]);
  }
  putchar('\n');
  return 0;
}
