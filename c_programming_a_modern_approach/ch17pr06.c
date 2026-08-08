#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 50
#define WORD_LEN 20

int compare_words(const void *p, const void *q);

int main(void) {
  char *words[MAX_WORDS], input[WORD_LEN + 1];
  int count = 0, i;

  while (count < MAX_WORDS) {
    printf("Enter word: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
      break;
    input[strcspn(input, "\n")] = '\0';
    if (input[0] == '\0')
      break;
    words[count] = malloc(strlen(input) + 1);
    if (words[count] == NULL) {
      printf("No space left.\n");
      break;
    }
    strcpy(words[count++], input);
  }

  qsort(words, count, sizeof(words[0]), compare_words);
  printf("In sorted order:");
  for (i = 0; i < count; i++) {
    printf(" %s", words[i]);
    free(words[i]);
  }
  putchar('\n');
  return 0;
}

int compare_words(const void *p, const void *q) {
  const char *const *left = p;
  const char *const *right = q;
  return strcmp(*left, *right);
}
