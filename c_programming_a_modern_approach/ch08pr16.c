#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

int main(void) {
  int counts[26] = {0}, ch;
  bool anagrams = true;

  printf("Enter first word: ");
  while ((ch = getchar()) != '\n' && ch != EOF)
    if (isalpha((unsigned char)ch))
      counts[tolower((unsigned char)ch) - 'a']++;

  printf("Enter second word: ");
  while ((ch = getchar()) != '\n' && ch != EOF)
    if (isalpha((unsigned char)ch))
      counts[tolower((unsigned char)ch) - 'a']--;

  for (int i = 0; i < 26; i++)
    if (counts[i] != 0)
      anagrams = false;

  printf(anagrams ? "The words are anagrams.\n"
                  : "The words are not anagrams.\n");
  return 0;
}
