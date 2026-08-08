#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool are_anagrams(const char *word1, const char *word2);

int main(void) {
  char word1[101], word2[101];

  printf("Enter first word: ");
  fgets(word1, sizeof(word1), stdin);
  word1[strcspn(word1, "\n")] = '\0';
  printf("Enter second word: ");
  fgets(word2, sizeof(word2), stdin);
  word2[strcspn(word2, "\n")] = '\0';
  printf("The words are %sanagrams.\n",
         are_anagrams(word1, word2) ? "" : "not ");
  return 0;
}

bool are_anagrams(const char *word1, const char *word2) {
  int counts[26] = {0}, i;

  while (*word1) {
    if (isalpha((unsigned char) *word1))
      counts[tolower((unsigned char) *word1) - 'a']++;
    word1++;
  }
  while (*word2) {
    if (isalpha((unsigned char) *word2))
      counts[tolower((unsigned char) *word2) - 'a']--;
    word2++;
  }
  for (i = 0; i < 26; i++)
    if (counts[i] != 0)
      return false;
  return true;
}
