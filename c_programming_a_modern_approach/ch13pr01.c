#include <stdio.h>
#include <string.h>

#define WORD_LEN 20

int main(void) {
  char word[WORD_LEN + 1], smallest[WORD_LEN + 1] = "";
  char largest[WORD_LEN + 1] = "";

  for (;;) {
    printf("Enter word: ");
    scanf("%20s", word);

    if (smallest[0] == '\0' || strcmp(word, smallest) < 0)
      strcpy(smallest, word);
    if (largest[0] == '\0' || strcmp(word, largest) > 0)
      strcpy(largest, word);
    if (strlen(word) == 4)
      break;
  }

  printf("Smallest word: %s\n", smallest);
  printf("Largest word: %s\n", largest);
  return 0;
}
