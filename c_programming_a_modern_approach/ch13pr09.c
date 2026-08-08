#include <ctype.h>
#include <stdio.h>

int compute_vowel_count(const char *sentence);

int main(void) {
  char sentence[201];

  printf("Enter a sentence: ");
  fgets(sentence, sizeof(sentence), stdin);
  printf("Your sentence contains %d vowels.\n",
         compute_vowel_count(sentence));
  return 0;
}

int compute_vowel_count(const char *sentence) {
  int count = 0;

  while (*sentence) {
    char ch = (char) tolower((unsigned char) *sentence++);
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
      count++;
  }
  return count;
}
